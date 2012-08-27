<?php
/**
 * @file
 *
 * Webform integration for EMT module.
 */

/**
 * Generate and output the emt webform table.
 */
function emt_webform_table($node) {
  $output = '';
  if (isset($node->emt['settings']['active']) && $node->emt['settings']['active']) {
    // Load and format all the data for this node.
    $rows = array();
    if (isset($node->emt['data'])) {
      foreach ($node->emt['data'] as $record) {
        // @TODO This could be refactored into a 'EMT Fields API' call in the future. 
        // Mapping all the different field types so they can be presented in the same table.
        $row['type'] = ucwords($record['type']);
        switch($record['type']) {
          case 'prospect':
          case 'reporting':
          case 'general':
            $row['id'] = $record['id'];
            $row['component'] = 'Component: \'' . $record['component'] . '\'';
            break;
          case 'optin':
            $row['id'] = 'Traction Optin Field';
            $row['component'] = ($record['component_or_custom'] == 1) ? 'Hardcoded: \'' . $record['custom'] . "'" : 'Component: \'' . $record['component'] . '\'';
            break;
          case 'attribute':
            $row['id'] = $record['id'];
            $attribute_types = _emt_get_traction_types();
            $row['component'] = 'Attribute Type: \'' . $attribute_types[$record['traction_attribute_type']] . '\', '; 
            $row['component'] .= ($record['component_or_custom'] == 1) ? ', Hardcoded: \'' . $record['custom'] . "'" : 'Component: \'' . $record['component'] . "'";
            break;
          case 'interaction':
            $row['id'] = $record['id'];
            $row['component'] = 'Function ID: \'' . $record['function_id'] . '\''. ', ';
            $row['component'] .= 'Extra Info: \'';
            $row['component'] .= ($record['component_or_custom'] == 1) ? "Hardcorded: " . $record['extra_info_custom'] ."'" : "Component: " . $record['extra_info_component'] . "'";
            break;
        }
        // Build the operations links.
        $row['operations'] = l('Edit', 'node/'.$node->nid.'/webform/emt/'.$record['type'].'/'.$record['eid'].'/edit') 
          .'&nbsp;&nbsp;&nbsp;&nbsp;'. l('Delete', 'node/'.$node->nid.'/webform/emt/'.$record['eid'].'/delete');
        $rows[] = $row;
      }

      // Output the table.
      if (!empty($rows)) {
        $header = array(
          t('Field Type'), 
          t('EMT Field Name / ID'), 
          t('Webform Component / Custom Value'), 
          t('Operations'),
        );
        $output .= theme('table', array(
          'header' => $header, 
          'rows' => $rows,
          'attributes' => array(
            'id' => 'webform-emt',
          ),
        ));
      }
      else {
        drupal_set_message('No EMT elements have been integrated with this form. Please add them using the links below.</p>');
      }
    }
    $path = 'node/'.$node->nid.'/webform/emt/';
    $output .= '+ ' . l('Add Prospect field', $path . 'prospect/add') . '&nbsp;&nbsp;&nbsp;&nbsp;';
    $output .= '+ ' . l('Add Reporting field', $path . 'reporting/add') . '&nbsp;&nbsp;&nbsp;&nbsp;';
    $output .= '+ ' . l('Add General field', $path . 'general/add') . '&nbsp;&nbsp;&nbsp;&nbsp;';
    $output .= '+ ' . l('Add Traction attribute', $path . 'attribute/add') . '&nbsp;&nbsp;&nbsp;&nbsp;';
    $output .= '+ ' . l('Add Traction interaction', $path . 'interaction/add') . '&nbsp;&nbsp;&nbsp;&nbsp;';
    $output .= '+ ' . l('Add Traction optin', $path . 'optin/add') . '&nbsp;&nbsp;&nbsp;&nbsp;';
  }
  else {
    drupal_set_message('You need to enable EMT integration on the EMT settings tab.');
  }
  return $output;
}


/**
 * FAPI for emt webform settings.
 */
function emt_webform_settings_form($form, $form_state, $node) {
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('EMT Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['settings']['active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable EMT integration for this webform'),
    '#description' => t('If this is not checked, no data will be sent to EMT for this form.'),
    '#default_value' => (isset($node->emt['settings']['active'])) ? $node->emt['settings']['active'] : '',
  );
  $form['settings']['nid'] = array(
    '#type' => 'hidden',
    '#value' => arg(1),
  );
  $form['settings']['lead_type'] = array(
    '#type' => 'select',
    '#title' => 'Lead Type',
    '#options' => _emt_leadtype_options(),
    '#description' => 'Enter the EMT lead type.',
    '#default_value' => (isset($node->emt['settings']['lead_type'])) ? $node->emt['settings']['lead_type'] : '',
    '#required' => TRUE,
  );
  $form['settings']['form_name'] = array(
    '#type' => 'textfield',
    '#title' => 'Form Name',
    '#description' => 'Enter the form name.',
    '#default_value' => (isset($node->emt['settings']['form_name'])) ? $node->emt['settings']['form_name'] : '',
    '#required' => TRUE,
    '#size' => 60,
    '#max_length' => 255,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
  return $form;
}

/**
 * FAPI submit for emt_webform_settings.
 */
function emt_webform_settings_form_submit($form, $form_state) {
  $values = $form_state['values'];
  db_delete('emt_webform_settings')
    ->condition('nid', $values['nid'])
    ->execute();
  db_insert('emt_webform_settings')
    ->fields(array(
      'nid' => $values['nid'],
      'active' => $values['active'],
      'lead_type' => $values['lead_type'],
      'form_name' => $values['form_name'],
    ))
    ->execute();
  drupal_set_message('The settings have been saved.');
}



/**
 * FAPI for adding a prospect field to a webform.
 */
function emt_webform_prospect_form($form, $form_state, $node, $eid = NULL) {
  if (isset($eid)) {
    $field = _emt_load_field($eid);
  }
  $form['field'] = array(
    '#type' => 'select',
    '#title' => t('Select prospect field'),
    '#description' => t('Select the EMT field to associate with.'),
    '#default_value' => (isset($field['id'])) ? $field['id'] : '',
    '#options' => _emt_prospect_field_options(),
  );
  $form['component'] = array(
    '#type' => 'select',
    '#title' => t('Select form component'),
    '#description' => t('Select the webform component'),
    '#default_value' => (isset($field['component'])) ? $field['component'] : '',
    '#options' => _emt_get_components($node),
  );
  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid,
  );
  $form['eid'] = array(
    '#type' => 'hidden',
    '#value' => $eid,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
  return $form;
}

/**
 * FAPI Submit for emt_webform_prospect_form.
 */
function emt_webform_prospect_form_submit($form, $form_state) {
  $values = $form_state['values'];
  db_delete('emt')
    ->condition('eid', $values['eid'])
    ->execute();
  db_insert('emt')
    ->fields(array(
      'eid' => $values['eid'],
      'nid' => $values['nid'],
      'type' => 'prospect',
      'value' => serialize(array('id' => $values['field'], 'component' => $values['component'])),
    ))
    ->execute();
  drupal_goto('node/'.$values['nid'].'/webform/emt');
}

/**
 * Deletes an EMT field.
 */
function emt_webform_field_delete($nid, $eid) {
  db_delete('emt')
    ->condition('eid', $eid)
    ->execute();
  drupal_set_message(t('The field has been deleted.'));
  drupal_goto('node/'.$nid.'/webform/emt');
}

/**
 * FAPI for adding a general field to a webform.
 */
function emt_webform_general_form($form, $form_state, $node, $eid = NULL) {
  if (isset($eid)) {
    $field = _emt_load_field($eid);
  }

  $form['field'] = array(
    '#type' => 'textfield',
    '#title' => t('Field to display as'),
    '#description' => t('Enter the general fields name as set in EMT.'),
    '#default_value' => (isset($field['id'])) ? $field['id'] : '',
    '#size' => '60',
    '#maxlength' => '128',
    '#required' => TRUE,
  );
  $form['component'] = array(
    '#type' => 'select',
    '#title' => t('Select form component'),
    '#description' => t('Select a webform component'),
    '#default_value' => (isset($field['component'])) ? $field['component'] : '',
    '#options' => _emt_get_components($node),
    '#required' => TRUE,
  );
  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid,
  );
  $form['eid'] = array(
    '#type' => 'hidden',
    '#value' => $eid,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
  return $form;
}

/**
 * FAPI Submit for emt_webform_general_form.
 */
function emt_webform_general_form_submit($form, $form_state) {
  $values = $form_state['values'];
  db_delete('emt')
    ->condition('eid', $values['eid'])
    ->execute();
  db_insert('emt')
    ->fields(array(
      'eid' => $values['eid'],
      'nid' => $values['nid'],
      'type' => 'general',
      'value' => serialize(array('id' => $values['field'], 'component' => $values['component'])),
    ))
    ->execute();
  drupal_goto('node/'.$values['nid'].'/webform/emt');
}

/**
 * FAPI for adding a traction field to a webform.
 */
function emt_webform_attribute_form($form, $form_state, $node, $eid = NULL) {
  if (isset($eid)) {
    $field = _emt_load_field($eid);
  }

  $form['field'] = array(
    '#type' => 'textfield',
    '#title' => t('Traction Attribute ID'),
    '#description' => t('Enter a traction attribute ID.'),
    '#size' => 60,
    '#max_length' => 255,
    '#default_value' => (isset($field['id'])) ? $field['id'] : '',
  );
  $form['traction_attribute_type'] = array(
    '#type' => 'select',
    '#title' => t('Traction Attribute Type'),
    '#description' => t('Select a traction attribute field type.'),
    '#options' => _emt_get_traction_types(),
    '#default_value' => (isset($field['traction_attribute_type'])) ? $field['traction_attribute_type'] : '',
  );
  $options = array(
    0 => t('Use a form component for this field'), 
    1 => t('Hardcode this field')
  );
  $form['component_or_custom'] = array(
    '#type' => 'radios',
    '#options' => $options,
    '#default_value' => (isset($field['component_or_custom'])) ? $field['component_or_custom'] : '',
  );
  $form['component'] = array(
    '#type' => 'select',
    '#title' => t('Select Webform component'),
    '#description' => t('Select a Webform component. The value of this component will be sent to EMT/Traction.'),
    '#default_value' => (isset($field['component'])) ? $field['component'] : '',
    '#options' => _emt_get_components($node),
    '#states' => array(
      'visible' => array(
        ':input[name="component_or_custom"]' => array('value' => 0),
      ),
    ),
  );
  $form['custom'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter hardcoded value.'),
    '#description' => t('Enter the text that will be sent to EMT/Traction'),
    '#default_value' => (isset($field['custom'])) ? $field['custom'] : '',
    '#states' => array(
      'visible' => array(
        ':input[name="component_or_custom"]' => array('value' => 1),
      ),
    ),
  );
  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid,
  );
  $form['eid'] = array(
    '#type' => 'hidden',
    '#value' => $eid,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
  return $form;
}

/**
 * FAPI Submit for emt_webform_traction_form.
 */
function emt_webform_attribute_form_submit($form, $form_state) {
  $values = $form_state['values'];
  db_delete('emt')
    ->condition('eid', $values['eid'])
    ->execute();
  db_insert('emt')
    ->fields(array(
      'eid' => $values['eid'],
      'nid' => $values['nid'],
      'type' => 'attribute',
      'value' => serialize(array(
        'id' => $values['field'], 
        'component' => $values['component'],
        'custom' => $values['custom'],
        'component_or_custom' => $values['component_or_custom'],
        'traction_attribute_type' => $values['traction_attribute_type'],
      )),
    ))
    ->execute();
  drupal_goto('node/'.$values['nid'].'/webform/emt');
}

/**
 * FAPI for adding a traction interaction to a webform.
 */
function emt_webform_interaction_form($form, $form_state, $node, $eid = NULL) {
  if (isset($eid)) {
    $field = _emt_load_field($eid);
  }
  $form['id'] = array(
    '#type' => 'textfield',
    '#title' => t('Interaction ID'),
    '#description' => t('Enter the interaction\'s id'),
    '#default_value' => (isset($field['id'])) ? $field['id'] : '',
    '#size' => 60,
    '#max_length' => 128,
  );
   $form['function_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Function ID'),
    '#description' => t('Enter the function id for this interaction'),
    '#default_value' => (isset($field['function_id'])) ? $field['function_id'] : '',
    '#size' => 60,
    '#max_length' => 128,
  );
  $form['extra_info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Extra Info'),
    '#collapsable' => FALSE,
  );
  $options = array(
    0 => t('Use a form component for this field'), 
    1 => t('Hardcode this field')
  );
  $form['extra_info']['component_or_custom'] = array(
    '#title' => t('Extra Info'),
    '#type' => 'radios',
    '#options' => $options,
    '#default_value' => (isset($field['component_or_custom'])) ? $field['component_or_custom'] : '',
  );
  $form['extra_info']['extra_info_custom'] = array(
    '#type' => 'textfield',
    '#title' => t('Hardcoded Value'),
    '#description' => 'Enter the text that will be sent to Traction.',
    '#default_value' => (isset($field['extra_info_custom'])) ? $field['extra_info_custom'] : '',
    '#size' => 60,
     '#states' => array(
      'visible' => array(
        ':input[name="component_or_custom"]' => array('value' => 1),
      ),
    ),
    '#max_length' => 128,
  );
  $form['extra_info']['extra_info_component'] = array(
    '#type' => 'select',
    '#title' => t('Select Webform component'),
    '#description' => t('Select a Webform component. The value of this component will be sent to EMT/Traction.'),
    '#default_value' => (isset($field['extra_info_component'])) ? $field['extra_info_component'] : '',
    '#options' => _emt_get_components($node),
    '#states' => array(
      'visible' => array(
        ':input[name="component_or_custom"]' => array('value' => 0),
      ),
    ),
  );
 $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid,
  );
  $form['eid'] = array(
    '#type' => 'hidden',
    '#value' => $eid,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
  return $form;
}

/**
 * FAPI Submit for emt_webform_interaction_form.
 */
function emt_webform_interaction_form_submit($form, $form_state) {
  $values = $form_state['values'];
  db_delete('emt')
    ->condition('eid', $values['eid'])
    ->execute();
  db_insert('emt')
    ->fields(array(
      'eid' => $values['eid'],
      'nid' => $values['nid'],
      'type' => 'interaction',
      'value' => serialize(array(
        'id' => $values['id'], 
        'component_or_custom' => $values['component_or_custom'],
        'extra_info_component' => $values['extra_info_component'], 
        'extra_info_custom' => $values['extra_info_custom'],
        'function_id' => $values['function_id'],

      )),
    ))
    ->execute();
  drupal_goto('node/'.$values['nid'].'/webform/emt');
}


/**
 * FAPI for adding a general field to a webform.
 */
function emt_webform_reporting_form($form, $form_state, $node, $eid = NULL) {
  if (isset($eid)) {
    $field = _emt_load_field($eid);
  }

  $form['field'] = array(
    '#type' => 'textfield',
    '#title' => t('Field to display as'),
    '#description' => t('Enter the reporting fields name as set in EMT.'),
    '#default_value' => (isset($field['id'])) ? $field['id'] : '',
    '#size' => '60',
    '#maxlength' => '128',
    '#required' => TRUE,
  );
  $form['component'] = array(
    '#type' => 'select',
    '#title' => t('Select form component'),
    '#description' => t('Select a webform component'),
    '#default_value' => (isset($field['component'])) ? $field['component'] : '',
    '#options' => _emt_get_components($node),
    '#required' => TRUE,
  );
  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid,
  );
  $form['eid'] = array(
    '#type' => 'hidden',
    '#value' => $eid,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
  return $form;
}

/**
 * FAPI Submit for emt_webform_general_form.
 */
function emt_webform_reporting_form_submit($form, $form_state) {
  $values = $form_state['values'];
  db_delete('emt')
    ->condition('eid', $values['eid'])
    ->execute();
  db_insert('emt')
    ->fields(array(
      'eid' => $values['eid'],
      'nid' => $values['nid'],
      'type' => 'reporting',
      'value' => serialize(array('id' => $values['field'], 'component' => $values['component'])),
    ))
    ->execute();
  drupal_goto('node/'.$values['nid'].'/webform/emt');
}


/**
 * FAPI for adding a general field to a webform.
 */
function emt_webform_optin_form($form, $form_state, $node, $eid = NULL) {
  if (isset($eid)) {
    $field = _emt_load_field($eid);
  }
  $options = array(
    0 => t('Use a form component for this field'), 
    1 => t('Hardcode this field')
  );
  $form['component_or_custom'] = array(
    '#type' => 'radios',
    '#options' => $options,
    '#default_value' => (isset($field['component_or_custom'])) ? $field['component_or_custom'] : '',
  );
 $form['component'] = array(
    '#type' => 'select',
    '#title' => t('Select form component'),
    '#description' => t('Select a webform component'),
    '#default_value' => (isset($field['component'])) ? $field['component'] : '',
    '#options' => _emt_get_components($node),
    '#required' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name="component_or_custom"]' => array('value' => 0),
      ),
    ),
  );
  $form['custom'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter hardcoded value.'),
    '#description' => t('Enter the text that will be sent to EMT/Traction'),
    '#default_value' => (isset($field['custom'])) ? $field['custom'] : '',
    '#required' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name="component_or_custom"]' => array('value' => 1),
      ),
    ),
  );
 
  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid,
  );
  $form['eid'] = array(
    '#type' => 'hidden',
    '#value' => $eid,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
  return $form;
}

/**
 * FAPI Submit for emt_webform_general_form.
 */
function emt_webform_optin_form_submit($form, $form_state) {
  $values = $form_state['values'];
  db_delete('emt')
    ->condition('eid', $values['eid'])
    ->execute();
  db_insert('emt')
    ->fields(array(
      'eid' => $values['eid'],
      'nid' => $values['nid'],
      'type' => 'optin',
      'value' => serialize(array(
        'component' => $values['component'],
        'custom' => $values['custom'],
        'component_or_custom' => $values['component_or_custom'],
      )),
    ))
    ->execute();
  drupal_goto('node/'.$values['nid'].'/webform/emt');
}
