<%@ Page Language="JScript" %>
<%@ Import Namespace="System" %>
<%@ Import Namespace="System.Data" %>
<%@ Import Namespace="System.Data.OleDb" %>
<%@ Register TagPrefix="Header" TagName="ImageHeader" Src="imageHeader.ascx" %>

<html>
   <body>
      <script language = "JScript" runat = "server">

         function Page_Load( sender : Object, events : EventArgs ) 
         {
            if ( !IsPostBack ) 
            {
               var dataBaseConnection : OleDbConnection = new 
                  OleDbConnection( ConfigurationSettings.AppSettings(
                  "ConnectionString" ) );
               
               var queryString : System.String = 
                  "SELECT lastName, firstName FROM Authors";

               dataBaseConnection.Open();
               
               var dataBaseCommand : OleDbCommand = 
                  new OleDbCommand( queryString, dataBaseConnection );
               
               var dataReader = dataBaseCommand.ExecuteReader();

               // while we read a row from result of 
               // query, add first item to drop down list
               while ( dataReader.Read() )
                  nameList.Items.Add( dataReader.GetString( 0 ) +
                  ", " + dataReader.GetString( 1 ) );
               
               // close database connection       
               dataBaseConnection.Close();
            }
            else 
            {
               dataGrid.DataSource = GetData();
               dataGrid.DataBind();
            }
         } // end Page_Load

         // Read a database and return the DataView
         function GetData() : ICollection 
         {
            var set : DataSet = new DataSet();
        
            // establish a connection, and query the database
            var dataBaseConnection: OleDbConnection = new 
               OleDbConnection( ConfigurationSettings.AppSettings(
               "ConnectionString" ) );
            
            var authorID : int = nameList.SelectedIndex + 1;
            
            var queryString : String =  
               "SELECT Titles.Title, Titles.ISBN, " +
               "Titles.Description FROM AuthorISBN " + 
               "INNER JOIN Titles ON AuthorISBN.ISBN = " + 
               "Titles.ISBN, Publishers WHERE " +
               "(AuthorISBN.AuthorID = " + authorID + ")";
            
            var dataBaseCommand : OleDbCommand = 
               new OleDbCommand( queryString, dataBaseConnection );
            
            var dataAdapter : OleDbDataAdapter = 
               new OleDbDataAdapter( dataBaseCommand );
            
            dataAdapter.Fill( set );
        
            // close database connection
            dataBaseCommand.Connection.Close();

            var dataView : DataView = new DataView( set.Tables[ 0 ] );
            dataView.Sort = "Title";
            
            return dataView;
         } // end GetData

      </script>

      <form runat = "server">

         <Header:ImageHeader id = "head" runat = "server"> 
         </Header:ImageHeader>
         <br />

         Authors:  
         <asp:DropDownList id = "nameList" runat = "server" 
            Width = "158px" Height = "22px">
         </asp:DropDownList>
         <asp:button id = "button" text = "select" runat = "server"> 
         </asp:button>
         <p>
            <asp:DataGrid id = "dataGrid" runat = "server" BackColor="#7CFC00" > 
                <HeaderStyle Font-Bold="True" ForeColor="#FFFFFF" VerticalAlign="Bottom"
					BackColor="#006400"></HeaderStyle>
                <AlternatingItemStyle BackColor="#90EE90"></AlternatingItemStyle>
            </asp:DataGrid>
         </p>

      </form>
   </body>
</html>