namespace ATM.WIN
{
    partial class Withdraw_UserControl
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
            this.components = new System.ComponentModel.Container();
            this.withdraw_button = new System.Windows.Forms.Button();
            this.account_type_label = new System.Windows.Forms.Label();
            this.account_type_dropdown = new System.Windows.Forms.ComboBox();
            this.amount_withdraw_label = new System.Windows.Forms.Label();
            this.amount_withdraw_box = new System.Windows.Forms.TextBox();
            this.errorProvider1 = new System.Windows.Forms.ErrorProvider(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).BeginInit();
            this.SuspendLayout();
            // 
            // withdraw_button
            // 
            this.withdraw_button.Location = new System.Drawing.Point(77, 210);
            this.withdraw_button.Name = "withdraw_button";
            this.withdraw_button.Size = new System.Drawing.Size(75, 23);
            this.withdraw_button.TabIndex = 10;
            this.withdraw_button.Text = "Submit";
            this.withdraw_button.UseVisualStyleBackColor = true;
            this.withdraw_button.Click += new System.EventHandler(this.withdraw_button_Click);
            // 
            // account_type_label
            // 
            this.account_type_label.AutoSize = true;
            this.account_type_label.Location = new System.Drawing.Point(77, 75);
            this.account_type_label.Name = "account_type_label";
            this.account_type_label.Size = new System.Drawing.Size(78, 13);
            this.account_type_label.TabIndex = 9;
            this.account_type_label.Text = "Withdraw From";
            // 
            // account_type_dropdown
            // 
            this.account_type_dropdown.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.account_type_dropdown.FormattingEnabled = true;
            this.account_type_dropdown.Location = new System.Drawing.Point(77, 94);
            this.account_type_dropdown.Name = "account_type_dropdown";
            this.account_type_dropdown.Size = new System.Drawing.Size(121, 21);
            this.account_type_dropdown.TabIndex = 8;
            // 
            // amount_withdraw_label
            // 
            this.amount_withdraw_label.AutoSize = true;
            this.amount_withdraw_label.Location = new System.Drawing.Point(74, 141);
            this.amount_withdraw_label.Name = "amount_withdraw_label";
            this.amount_withdraw_label.Size = new System.Drawing.Size(107, 13);
            this.amount_withdraw_label.TabIndex = 6;
            this.amount_withdraw_label.Text = "Amount To Withdraw";
            // 
            // amount_withdraw_box
            // 
            this.amount_withdraw_box.Location = new System.Drawing.Point(77, 158);
            this.amount_withdraw_box.Name = "amount_withdraw_box";
            this.amount_withdraw_box.Size = new System.Drawing.Size(100, 20);
            this.amount_withdraw_box.TabIndex = 7;
            this.amount_withdraw_box.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // errorProvider1
            // 
            this.errorProvider1.ContainerControl = this;
            // 
            // Withdraw_UserControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.Controls.Add(this.withdraw_button);
            this.Controls.Add(this.account_type_label);
            this.Controls.Add(this.account_type_dropdown);
            this.Controls.Add(this.amount_withdraw_label);
            this.Controls.Add(this.amount_withdraw_box);
            this.Name = "Withdraw_UserControl";
            this.Title = "Withdraw";
            this.Controls.SetChildIndex(this.amount_withdraw_box, 0);
            this.Controls.SetChildIndex(this.amount_withdraw_label, 0);
            this.Controls.SetChildIndex(this.account_type_dropdown, 0);
            this.Controls.SetChildIndex(this.account_type_label, 0);
            this.Controls.SetChildIndex(this.withdraw_button, 0);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button withdraw_button;
        private System.Windows.Forms.Label account_type_label;
        private System.Windows.Forms.ComboBox account_type_dropdown;
        private System.Windows.Forms.Label amount_withdraw_label;
        private System.Windows.Forms.TextBox amount_withdraw_box;
        private System.Windows.Forms.ErrorProvider errorProvider1;
    }
}
