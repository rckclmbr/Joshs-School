namespace ATM.WIN
{
    partial class Balance_UserControl
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.checking_balance_label = new System.Windows.Forms.Label();
            this.savings_balance_label = new System.Windows.Forms.Label();
            this.checking_balance_box = new System.Windows.Forms.TextBox();
            this.savings_balance_box = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // checking_balance_label
            // 
            this.checking_balance_label.AutoSize = true;
            this.checking_balance_label.Location = new System.Drawing.Point(40, 114);
            this.checking_balance_label.Name = "checking_balance_label";
            this.checking_balance_label.Size = new System.Drawing.Size(137, 13);
            this.checking_balance_label.TabIndex = 1;
            this.checking_balance_label.Text = "Checking Account Balance";
            this.checking_balance_label.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // savings_balance_label
            // 
            this.savings_balance_label.AutoSize = true;
            this.savings_balance_label.Location = new System.Drawing.Point(39, 186);
            this.savings_balance_label.Name = "savings_balance_label";
            this.savings_balance_label.Size = new System.Drawing.Size(130, 13);
            this.savings_balance_label.TabIndex = 2;
            this.savings_balance_label.Text = "Savings Account Balance";
            // 
            // checking_balance_box
            // 
            this.checking_balance_box.Enabled = false;
            this.checking_balance_box.Location = new System.Drawing.Point(43, 131);
            this.checking_balance_box.Name = "checking_balance_box";
            this.checking_balance_box.Size = new System.Drawing.Size(134, 20);
            this.checking_balance_box.TabIndex = 3;
            this.checking_balance_box.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // savings_balance_box
            // 
            this.savings_balance_box.Enabled = false;
            this.savings_balance_box.Location = new System.Drawing.Point(43, 203);
            this.savings_balance_box.Name = "savings_balance_box";
            this.savings_balance_box.Size = new System.Drawing.Size(134, 20);
            this.savings_balance_box.TabIndex = 4;
            this.savings_balance_box.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // Balance_UserControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.Controls.Add(this.savings_balance_box);
            this.Controls.Add(this.checking_balance_box);
            this.Controls.Add(this.savings_balance_label);
            this.Controls.Add(this.checking_balance_label);
            this.Name = "Balance_UserControl";
            this.Title = "Welcome";
            this.Controls.SetChildIndex(this.checking_balance_label, 0);
            this.Controls.SetChildIndex(this.savings_balance_label, 0);
            this.Controls.SetChildIndex(this.checking_balance_box, 0);
            this.Controls.SetChildIndex(this.savings_balance_box, 0);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label checking_balance_label;
        private System.Windows.Forms.Label savings_balance_label;
        private System.Windows.Forms.TextBox checking_balance_box;
        private System.Windows.Forms.TextBox savings_balance_box;
    }
}
