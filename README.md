
EMT Module
----------


### HANDLING CONTEXT SENSITIVE DATA ###

This is stuff like passing the information about a specific home
into EMT when those fields are not on the webform.

Context sensitive information that is not directly related to the webform can 
be passed into EMT by adding hidden fields to the webform then altering the form 
to fill the hidden fields before sending to EMT.

For example:

/**
 * Implements hook_form_FORM_ID_alter().
 */
function emt_form_webform_client_form_251_alter(&$form, &$form_state) {
  $form['submitted']['homename']['#value'] = 'Send this text through!';
}

Alternatively you might be loading the form array with drupal_get_form() then editing
the submitted fields in the next line.


### EMT ARRAY STRUCTURE ###

The EMT array should be structured as follows. This array will be converted to
a POST request by emt_post().

Note that in order to have 'item's with the same name in xml, we have to wrap 
these fields in numerical arrays.

$data = array(
  'prospect' => array(
    'firstname' => '',
    'lastname' => '',
    'email' => '',
    'email2' => '',
    'phone' => '',
    'phone2' => '',
    'mobile' => '',
  ),
  'reporting' => array(
    'homeName' => '',
    'buildLocation' => '',
    'housePrice' => '',
    'houselandSuburb' => '',
    'houselandPrice' => '',
    'refererSource' => '',
    'refererMedium' => '',
    'refererCampaign' => '',
  ),
  'generalFields' => array(
    array(
      'item' => array(
        'fieldName' => '',
        'fieldValue' => '',
      ),
    ),
    array(
      'item' => array(
        'fieldName' => '',
        'fieldValue' => '',
      ),
    ),
    array(
      'item' => array(
        'fieldName' => '',
        'fieldValue' => '',
      ),
    ),
    array(
      'item' => array(
        'fieldName' => '',
        'fieldValue' => '',
      ),
    ),
    array(
      'item' => array(
        'fieldName' => '',
        'fieldValue' => '',
      ),
    ),
  ),
  'traction' => array(
    'option' => 'Yes',
    'customAttributes' => array(
      array(
        'itemCA' => array(
          'fieldName' => '',
          'fieldValue' => '',
          'fieldType' => '',
        ),
      ),
      array(
        'itemCA' => array(
          'fieldName' => '',
          'fieldValue' => '',
          'fieldType' => '',
        ),
      ),
      array(
        'itemCA' => array(
          'fieldName' => '',
          'fieldValue' => '',
          'fieldType' => '',
        ),
      ),
    ),
    'interactions' => array(
      array(
        'interact' => array(
          'functionID' => '',
          'interactionID' => '',
          'extraInfo' => '',
        ),
      ),
    ),
  ),
);

