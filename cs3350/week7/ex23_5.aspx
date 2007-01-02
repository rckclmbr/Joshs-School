<%@ Page Language="JScript" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" 
    "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
    <head>
        <title>Assignment 23.5</title>
        
    </head>
    <body>
        <form method="post" action="Default.aspx" runat="server" id="theForm">
            <h1>Enter your credit card information:</h1>
            
            Cardholder:
            <asp:TextBox ID="cardholder" runat="server" />
            <asp:RequiredFieldValidator
                ID="cardholdervalidator"
                Display="None"
                ControlToValidate="cardholder" runat="server"
				ErrorMessage="Cardholder name required" />
            
            <br /><br />
            
            Card number:
            <asp:TextBox ID="cardnumber" runat="server" />
            <asp:RequiredFieldValidator
                ID="cardnumbervalidator"
                Display="None"
                ControlToValidate="cardnumber" runat="server"
				ErrorMessage="Cardnumber required" />
            <asp:RegularExpressionValidator 
                ID="cardnumberexpression"
                Display="None"
                ControlToValidate="cardnumber"
                runat="server"
                ValidationExpression="^\d+$"
				ErrorMessage="Do not enter spaces or dashes.  Make sure you entered numbers." />
            
            <br /><br />
            
            Expiration (MM/YY):                
            <asp:TextBox ID="expiration" runat="server" />
            <asp:RequiredFieldValidator
                ID="expirationvalidator"
                Display="None"
                ControlToValidate="expiration" runat="server"
                ErrorMessage="Expiration date required." />
            <asp:RegularExpressionValidator ID="expirationexpression" 
                Display="None"
                ControlToValidate="expiration"
                runat="server"
                ValidationExpression="\d{2}/\d{2}"
                ErrorMessage="Incorrect expiration date format." />
            
            <br /><br />
            
            Payment type:
            <asp:DropDownList runat="server">
                <asp:ListItem Value="Visa">Visa</asp:ListItem>
                <asp:ListItem Value="Mastercard">Mastercard</asp:ListItem>
                <asp:ListItem Value="Discovery">Discovery</asp:ListItem>
            </asp:DropDownList>
            
            <br /><br />
            
            <asp:Button Text="Submit" runat="server" />
            
            <asp:ValidationSummary  ID="summary" runat="server" />
            
        </form>
  
    </body>
</html>
