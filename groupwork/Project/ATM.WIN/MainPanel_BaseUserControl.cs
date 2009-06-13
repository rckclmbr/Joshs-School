using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using ATM.BLL;

namespace ATM.WIN
{
    public partial class MainPanel_BaseUserControl : UserControl
    {
        protected Main owner;

        #region constructors
        public MainPanel_BaseUserControl()
        {
            InitializeComponent();
        }

        public MainPanel_BaseUserControl(Main owner)
        {
            this.owner = owner;
            InitializeComponent();
        }
        #endregion constructors

        public String Title {
            get { return this.title.Text; }
            set { this.title.Text = value; }
        }

        protected virtual void Repaint(object sender, EventArgs e)
        {}

    }
}       
