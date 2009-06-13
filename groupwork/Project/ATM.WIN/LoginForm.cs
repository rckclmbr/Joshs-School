using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ATM.DAL;
using ATM.BLL;

namespace ATM.WIN
{
    public partial class LoginForm : Form
    {
        private static CustomerDB customerDB = new CustomerDB();

        #region constructors
        public LoginForm()
        {
            InitializeComponent();

        }

        #endregion constructors

        #region event methods
        private void LoginForm_Load(object sender, EventArgs e)
        {

        }

        private void login_button_Click(object sender, EventArgs e)
        {
            string userId = this.acctnum_textbox.Text;
            string pin = this.pin_textbox.Text;

            Customer customer = TryLogin(userId, pin);

            if (customer != null)
            {
                ((Main)(this.Owner)).Customer = customer;
                this.DialogResult = DialogResult.OK;
                this.Close();
            }
            else
            {
                this.Error_Label.Text = "Invalid Login";
            }
        }

        #endregion event methods

        #region private methods
        private Customer TryLogin(string userId, string pin)
        {
            short nPin = 0;

            if (Int16.TryParse(pin, out nPin) == false)
            {
                this.errorProvider1.SetError(this.pin_textbox, "Invalid pin entered.");
                return null;
            }

            Customer customer = customerDB.GetCustomerObject(userId, nPin);
            customer.Accounts = customerDB.GetAccounts(customer.CustomerNumber);

            if (!(customer.CustomerNumber > 0 && customer.Status == ObjectStatus.Clean))
            {
                this.errorProvider1.SetError(this.pin_textbox, "Invalid Account Number / PIN.");
                return null;
            }
            return customer;


        }
        #endregion private methods

    }
}