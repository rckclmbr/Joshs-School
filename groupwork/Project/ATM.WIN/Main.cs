using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ATM.BLL;
using ATM.DAL;

namespace ATM.WIN
{
    public partial class Main : Form
    {
        private Customer customer = new Customer();
        private Panel mainPanel;
        private LoginForm login;
        private MainPanel_BaseUserControl right_usercontrol;
        private static CustomerDB customerDB = new CustomerDB();

        private CheckingAccount cAccount = new CheckingAccount();
        private SavingsAccount sAccount = new SavingsAccount();

        public Main()
        {
            InitializeComponent();

            // Shorthand for our panels
            this.mainPanel = this.splitContainer2.Panel2;

            // Add default panels
            this.Visible = true;

            //
            // UserControls for right panel
            //
            b = new Balance_UserControl(this);
            t = new Transfer_UserControl(this);
            d = new Deposit_UserControl(this);
            w = new Withdraw_UserControl(this);

            login = new LoginForm();
            login.FormClosed += new FormClosedEventHandler(login_FormClosed);
            login.ShowDialog(this);
        }

        void login_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (login.DialogResult == DialogResult.OK)
            {

                // Populate toolbar with accounts
                List<String> accountNums = customer.AccountNumbers;

                foreach (String i in accountNums)
                {
                    this.accountsComboBox.Items.Add(i);
                }

                this.right_usercontrol = b;

                // Default to the first account
                this.accountsComboBox.SelectedIndex = 0;

                // Display main user control
                this.mainPanel.Controls.Add(this.right_usercontrol);

            }
            else if (login.DialogResult == DialogResult.Cancel)
            {
                // They cancelled
                this.treeView1.Enabled = false;
            }

        }

        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {

            if (e.Node.Text == "Main")
            {
                this.right_usercontrol = b;
            } 
            else if (e.Node.Text.Equals("Withdraw")) 
            {
                this.right_usercontrol = w;
            }
            else if (e.Node.Text.Equals("Transfer"))
            {
                this.right_usercontrol = t;
            }
            else if (e.Node.Text.Equals("Deposit")) 
            {
                this.right_usercontrol = d;
            }


            this.right_usercontrol.Visible = false;
            this.mainPanel.Controls.Clear();
            this.mainPanel.Controls.Add(this.right_usercontrol);
            this.right_usercontrol.Visible = true;
             
        }

        // When they change the account from the dropdown
        private void accountsComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.right_usercontrol = b;
            

            // Get what they changed it to
            String acctNum = this.accountsComboBox.Text;
            List<Account> accts = this.customer.Accounts;
            
            bool has_savings = false, has_checking = false; // Used for settings savings or checking to null
            foreach (Account i in accts)
            {
                if (i.AccountNumber.ToString() == acctNum)
                {
                    if (i is SavingsAccount)
                    {
                        this.SAccount = (SavingsAccount)i;
                        has_savings = true;
                    }
                    else if (i is CheckingAccount)
                    {
                        this.CAccount = (CheckingAccount)i;
                        has_checking = true;
                    }
                }
            }
            if (!has_checking) this.CAccount = null;
            if (!has_savings) this.SAccount = null;

            this.right_usercontrol.Visible = false;
            this.treeView1.SelectedNode = this.treeView1.Nodes[0];
            this.right_usercontrol.Visible = true;
        }

        public void UpdateAccounts()
        {
            if (SAccount != null) customerDB.SaveAccount(this.SAccount);
            if (CAccount != null) customerDB.SaveAccount(this.CAccount);
        }

        #region properties
        public CheckingAccount CAccount
        {
            set { this.cAccount = (CheckingAccount)value; }
            get { return this.cAccount; }
        }
        public SavingsAccount SAccount
        {
            set { this.sAccount = value; }
            get { return this.sAccount; }
        }
        public Customer Customer
        {
            get { return this.customer; }
            set { this.customer = value; }
        }
        #endregion properties

        // Our user controls for the main window
        private Balance_UserControl b;
        private Transfer_UserControl t;
        private Deposit_UserControl d;
        private Withdraw_UserControl w;

    }
}