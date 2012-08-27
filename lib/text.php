<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Untitled Document</title>
<style type="text/css">
body { margin:10px; padding:0; font-size:13px; font-family:Arial, Helvetica, sans-serif; color: #343434; line-height:20px; }
h1 { font-size:24px; font-weight:bold; }
h2 { font-size:18px; font-weight:bold; padding: 0 0 10px; margin:0; }
.text_field { border:1px solid #ddd; font-size:14px; padding:4px; width:165px; height:19px; margin:0; -moz-border-radius:5px; -webkit-border-radius:5px; }
.dropbox { border:1px solid #ddd; font-size:14px; padding:4px; width:174px; white-space: pre; margin:0; -moz-border-radius:5px; -webkit-border-radius:5px; }
.text_field:focus{ border-color:#aaa; background-color:#fafafa; }

</style>
</head>

<body>
<H1>EMT Test XML Creation<br />
</H1>
<form name="enquiry" id="enquiry" method="post">
<div style="border:1px solid #999; border-radius:10px; padding:10px; -moz-border-radius:10px; -webkit-border-radius:10px; width:945px;">
  <h2>Visable Form Fields</h2>
  <div style="float:left; margin-right:30px;">
  <table border="0" cellspacing="0" cellpadding="3">
    <tr>
      <td colspan="2"><strong>Standard Fields</strong></td>
    </tr>
    <tr>
      <td>First Name:</td>
      <td><input type="text" name="firstname" id="firstname" class="text_field" /></td>
    </tr>
    <tr>
      <td>Surname:</td>
      <td><input type="text" name="lastname" id="lastname" class="text_field" /></td>
    </tr>
    <tr>
      <td>Email Address:</td>
      <td><input type="text" name="email" id="email" class="text_field" /></td>
    </tr>
    <tr>
      <td>Phone:</td>
      <td><input type="text" name="phone" id="phone" class="text_field" /></td>
    </tr>
    <tr>
      <td>Mobile:</td>
      <td><input type="text" name="mobile" id="mobile" class="text_field" /></td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td>&nbsp;</td>
    </tr>
  </table>
  </div>
  <div style="float:left; margin-right:30px;">
  <table border="0" cellspacing="0" cellpadding="3">
    <tr>
      <td colspan="2"><strong>Optional Fields</strong></td>
    </tr>
    <tr>
      <td>Email Address 2:</td>
      <td><input type="text" name="email2" id="email2" class="text_field" /></td>
    </tr>
    <tr>
      <td>Phone 2:</td>
      <td><input type="text" name="phone2" id="phone2" class="text_field" /></td>
    </tr>
    <tr>
      <td>Mobile 2:</td>
      <td><input type="text" name="mobile2" id="mobile2" class="text_field" /></td>
    </tr>
    <tr>
      <td>Location:</td>
      <td><input type="radio" name="location" id="location" value="Perth Metro" />
        <label for="location" style="padding-right:15px;">Perth Metro</label><input type="radio" name="location" id="location2" value="South West" />
        <label for="location2">South West</label></td>
    </tr>
    <tr>
      <td>First Home Buyer:</td>
      <td><input type="radio" name="firsthome" id="firsthome1" value="Yes" />
        <label for="firsthome1" style="padding-right:15px;">Yes</label>
        <input type="radio" name="firsthome" id="firsthome2" value="No" />
        <label for="firsthome2">No</label></td>
    </tr>
    <tr>
      <td>Opt-in Newsletter:</td>
      <td><input name="opt-in" type="checkbox" id="opt-in" value="Yes" />
        <label for="opt-in">Yes, I would like to receive junk in my email account</label></td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td>&nbsp;</td>
    </tr>
  </table>
  </div>
  <div style="clear:both"></div>
</div>
<br />
<div style="border:1px solid #999; border-radius:10px; padding:10px; -moz-border-radius:10px; -webkit-border-radius:10px; width:945px;">
  <h2>Hidden Form Fields</h2>
  <div style="float:left; margin-right:30px;">
    <table border="0" cellspacing="0" cellpadding="3">
      <tr>
        <td colspan="2"><strong>Required</strong></td>
      </tr>
      <tr>
        <td>Company ID:</td>
        <td><input type="text" name="companyID" id="companyID" class="text_field" /></td>
      </tr>
      <tr>
        <td>Lead Type:</td>
        <td><input type="text" name="leadtype" id="leadtype" class="text_field" /></td>
      </tr>
      <tr>
        <td>Form Name:</td>
        <td><input type="text" name="formname" id="formname" class="text_field" /></td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td>Referer</td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td>Source:</td>
        <td><input type="text" name="source" id="source" class="text_field" /></td>
      </tr>
      <tr>
        <td>Medium:</td>
        <td><input type="text" name="medium" id="medium" class="text_field" /></td>
      </tr>
      <tr>
        <td>Campaign:</td>
        <td><input type="text" name="campaign" id="campaign" class="text_field" /></td>
      </tr>
    </table>
  </div>
  <div style="float:left; margin-right:30px;">
    <table border="0" cellspacing="0" cellpadding="3">
      <tr>
        <td colspan="2"><strong>Reporting</strong></td>
      </tr>
      <tr>
        <td>Home Name:</td>
        <td><input type="text" name="homename" id="homename" class="text_field" /></td>
      </tr>
      <tr>
        <td>Build Location:</td>
        <td><input type="text" name="buildlocation" id="textfield7" class="text_field" /></td>
      </tr>
      <tr>
        <td>House Price:</td>
        <td><input type="text" name="houseprice" id="textfield8" class="text_field" /></td>
      </tr>
      <tr>
        <td>House/Land Suburb:</td>
        <td><input type="text" name="houselandsuburb" id="textfield9" class="text_field" /></td>
      </tr>
      <tr>
        <td>House/Land Price:</td>
        <td><input type="text" name="houselandprice" id="textfield10" class="text_field" /></td>
      </tr>
    </table>
  </div>
  <div style="float:left;">
    <table border="0" cellspacing="0" cellpadding="3">
      <tr>
        <td colspan="2"><strong>Traction</strong></td>
      </tr>
      <tr>
        <td>Traction ID:</td>
        <td><input type="text" name="tractionid" id="tractionid" class="text_field" /></td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td colspan="2">Custom Attributes:eg: fieldName|fieldValue|fieldType</td>
        </tr>
      <tr>
        <td>1</td>
        <td><input name="attribute[]" type="text" class="text_field" id="attribute[]" /></td>
      </tr>
      <tr>
        <td>2</td>
        <td><input name="attribute[]" type="text" class="text_field" id="attribute[]" /></td>
      </tr>
      <tr>
        <td>3</td>
        <td><input name="attribute[]" type="text" class="text_field" id="attribute[]" /></td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td colspan="2">Interactions&nbsp;&nbsp;&nbsp; eg: functionID|interactID|extraInfo</td>
        </tr>
      <tr>
        <td>Custom Interaction 1:</td>
        <td><input name="interaction[]" type="text" class="text_field" id="interaction[]" /></td>
      </tr>
      <tr>
        <td>Custom Interaction 2:</td>
        <td><input name="interaction[]" type="text" class="text_field" id="interaction[]" /></td>
      </tr>
      <tr>
        <td>Custom Interaction 3:</td>
        <td><input name="interaction[]" type="text" class="text_field" id="interaction[]" /></td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
      </tr>
    </table>
  </div>
  <div style="clear:both"></div>
</div>
<br />
<div align="center" style=" width:965px;"><input type="button" name="doStuff" id="doStuff" value="Submit Values For Testing" /></div>
<div id="processInfo"></div>
</form>

<script src="jquery.js" type="text/javascript"></script>
<script type="text/javascript">
	$("#doStuff").bind("click",function() {
		var info = $("#enquiry").serialize();
		$("#processInfo").html('Processing...');
		$.post("processEnquiry.php", info, function(data){
			setTimeout(function() { 
				$("#processInfo").html(data);
			},1000 );
		});
	});
</script>
</body>
</html>