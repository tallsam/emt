<?		
//for all other dealers, send lead to autogate using CURL/XML

//Build XML
//Required HTTP Header Values
//Target URL
$sendto = "https://emt.abngroup.com.au/EMTWebservices.asmx?op=ImportEMTData";

$interact = $attribute = '';
foreach ($_POST['interaction'] AS $val) {
	$values = explode('|',$val);
	$interact .= '            <interact>
                <functionID>'.htmlentities($values[0],ENT_QUOTES,'ISO-8859-1').'</functionID>
                <interactionID>'.htmlentities($values[1],ENT_QUOTES,'ISO-8859-1').'</interactionID>
                <extraInfo>'.htmlentities($values[2],ENT_QUOTES,'ISO-8859-1').'</extraInfo>
            </interact>
';	
}
foreach ($_POST['attribute'] AS $val) {
	$values = explode('|',$val);
	$attribute .= '            <itemCA>
                <fieldName>'.htmlentities($values[0],ENT_QUOTES,'ISO-8859-1').'</fieldName>
                <fieldValue>'.htmlentities($values[1],ENT_QUOTES,'ISO-8859-1').'</fieldValue>
                <fieldType>'.htmlentities($values[2],ENT_QUOTES,'ISO-8859-1').'</fieldType>
            </itemCA>

';	
}

$att1 = explode('|',$_POST['attribute1']);
//XML Data
$post = '<?xml version="1.0" encoding="UTF-8"?>
<lead xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="EMT.xsd">
    <companyID>'.htmlentities($_POST['companyID'],ENT_QUOTES,'ISO-8859-1').'</companyID>
    <leadType>'.htmlentities($_POST['leadtype'],ENT_QUOTES,'ISO-8859-1').'</leadType>
    <formName>'.htmlentities($_POST['formname'],ENT_QUOTES,'ISO-8859-1').'</formName>
    <referer>
        <source>'.htmlentities($_POST['source'],ENT_QUOTES,'ISO-8859-1').'</source>
        <medium>'.htmlentities($_POST['medium'],ENT_QUOTES,'ISO-8859-1').'</medium>
        <campaign>'.htmlentities($_POST['campaign'],ENT_QUOTES,'ISO-8859-1').'</campaign>
    </referer>
    <prospect>
        <firstname>'.htmlentities($_POST['firstname'],ENT_QUOTES,'ISO-8859-1').'</firstname>
        <lastname>'.htmlentities($_POST['lastname'],ENT_QUOTES,'ISO-8859-1').'</lastname>
        <email>'.htmlentities($_POST['email'],ENT_QUOTES,'ISO-8859-1').'</email>
        <email2>'.htmlentities($_POST['email2'],ENT_QUOTES,'ISO-8859-1').'</email2>
        <phone>'.htmlentities($_POST['phone'],ENT_QUOTES,'ISO-8859-1').'</phone>
        <phone2>'.htmlentities($_POST['phone2'],ENT_QUOTES,'ISO-8859-1').'</phone2>
        <mobile>'.htmlentities($_POST['mobile'],ENT_QUOTES,'ISO-8859-1').'</mobile>
        <mobile2>'.htmlentities($_POST['mobile2'],ENT_QUOTES,'ISO-8859-1').'</mobile2>
    </prospect>
    <reporting>
        <homeName>'.htmlentities($_POST['homename'],ENT_QUOTES,'ISO-8859-1').'</homeName>
        <buildLocation>'.htmlentities($_POST['buildlocation'],ENT_QUOTES,'ISO-8859-1').'</buildLocation>
        <housePrice>'.htmlentities($_POST['houseprice'],ENT_QUOTES,'ISO-8859-1').'</housePrice>
        <houselandSuburb>'.htmlentities($_POST['houselandsuburb'],ENT_QUOTES,'ISO-8859-1').'</houselandSuburb>
        <houselandPrice>'.htmlentities($_POST['houselandprice'],ENT_QUOTES,'ISO-8859-1').'</houselandPrice>
        <refererSource>'.htmlentities($_POST['source'],ENT_QUOTES,'ISO-8859-1').'</refererSource>
        <refererMedium>'.htmlentities($_POST['medium'],ENT_QUOTES,'ISO-8859-1').'</refererMedium>
        <refererCampaign>'.htmlentities($_POST['campaign'],ENT_QUOTES,'ISO-8859-1').'</refererCampaign>
    </reporting>
    <generalFields>
        <item>
            <fieldName>Location</fieldName>
            <fieldValue>'.htmlentities($_POST['location'],ENT_QUOTES,'ISO-8859-1').'</fieldValue>
        </item>
        <item>
            <fieldName>First Home Buyer</fieldName>
            <fieldValue>'.htmlentities($_POST['firsthome'],ENT_QUOTES,'ISO-8859-1').'</fieldValue>
        </item>
        <item>
            <fieldName>Opt In</fieldName>
            <fieldValue>'.htmlentities($_POST['opt-in'],ENT_QUOTES,'ISO-8859-1').'</fieldValue>
        </item>
    </generalFields>	
    <traction>
        <tractionID>152</tractionID>
        <optIn>'.htmlentities($_POST['opt-in'],ENT_QUOTES,'ISO-8859-1').'</optIn>
        <customAttributes>
'.$attribute.'
        </customAttributes>
        <interactions>
'.$interact.'
        </interactions>
    </traction>   
</lead>';
	

include("nusoap/nusoap.php");
$client = new soapclient('https://emt.abngroup.com.au/EMTWebservices.asmx?wsdl',true);
$err = $client->getError();
if ($err) {
	echo '<h2>Constructor error</h2><pre>' . $err . '</pre>';
}
//debug messages
$client->debug_flag = 1;
print_r($client -> call(array('strData'=> stripslashes($post))));
echo '<br>-----------------------------<br>';
$params = array ('strData' =>  stripslashes($post));
$result = $client -> call("ImportEMTData", $params );
if ($client->fault) {
	echo '<h2>Fault</h2><pre>'; print_r($result); echo '</pre>';
} else {
	$err = $client->getError();
	if ($err) {
		echo '<h2>Error</h2><pre>' . $err . '</pre>';
	} else {
		echo '<h2>Result</h2><pre>'; print_r($result); echo '</pre>';
	}
}





?>
