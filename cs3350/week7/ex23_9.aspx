<%@ Page Language="JScript" %>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD XHTML 1.1//EN"
	"http://www.w3.org/TR/xhtml11/DTD.xhtml11.dtd" >

<html xmlns="http://www.w3.org/1999/xhtml" >
	<head>
		<title>Assignment 23.9</title>
		
		<script runat="server">
		
			function Page_Load() {
				
				if (!IsPostBack) {
					
					var numVisits : int;
				
					if (Request.Cookies("visit") == null) {
						numTimes.Text = "You have visited this site 1 time.";
						Response.Cookies("visit").Value = 1;
					} else {
						numVisits = parseInt(Request.Cookies("visit").Value);
						numTimes.Text = "You have visited this site " + (numVisits + 1) + " times.";
						Response.Cookies("visit").Value = numVisits + 1;
					}
				
					var time : DateTime = DateTime.Now;
					Response.Cookies("visit").Expires = time.AddDays(1);
					
				}
				
			}
			
		</script>
	
	</head>
	
	<body>
	
		<form action="ex23_9.aspx" method="post" runat="server">
		
			<asp:Button id="home" Text="home" Runat="server"></asp:Button>
			<asp:Button id="pictures" Text="pictures" Runat="server"></asp:Button>
			<asp:Button id="links" Text="links" Runat="server"></asp:Button>
			<asp:Button id="resume" Text="resume" Runat="server"></asp:Button>
			<br /><br />
			<asp:Label ID="numTimes" Runat="server"></asp:Label>
			
		</form>
		
	</body>
</html>
