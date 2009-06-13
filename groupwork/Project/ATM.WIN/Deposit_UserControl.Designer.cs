namespace ATM.WIN
{
    partial class Deposit_UserControl
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
            this.amount_deposit_label = new System.Windows.Forms.Label();
            this.amount_deposit_box = new System.Windows.Forms.TextBox();
            this.account_type_dropdown = new System.Windows.Forms.ComboBox();
            this.account_type_label = new System.Windows.Forms.Label();
            this.deposit_button = new System.Windows.Forms.Button();
            this.errorProvider1 = new System.Windows.Forms.ErrorProvider(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).BeginInit();
            this.SuspendLayout();
            // 
            // amount_deposit_label
            // 
            this.amount_deposit_label.AutoSize = true;
            this.amount_deposit_label.Location = new System.Drawing.Point(56, 145);
            this.amount_deposit_label.Name = "amount_deposit_label";
            this.amount_deposit_label.Size = new System.Drawing.Size(98, 13);
            this.amount_deposit_label.TabIndex = 1;
            this.amount_deposit_label.Text = "Amount To Deposit";
            // 
            // amount_deposit_box
            // 
            this.amount_deposit_box.Location = new System.Drawing.Point(59, 162);
            this.amount_deposit_box.Name = "amount_deposit_box";
            this.amount_deposit_box.Size = new System.Drawing.Size(100, 20);
            this.amount_deposit_box.TabIndex = 2;
            this.amount_deposit_box.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // account_type_dropdown
            // 
            this.account_type_dropdown.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.account_type_dropdown.FormattingEnabled = true;
            this.account_type_dropdown.Location = new System.Drawing.Point(59, 98);
            this.account_type_dropdown.Name = "account_type_dropdown";
            this.account_type_dropdown.Size = new System.Drawing.Size(121, 21);
            this.account_type_dropdown.TabIndex = 3;
            // 
            // account_type_label
            // 
            this.account_type_label.AutoSize = true;
            this.account_type_label.Location = new System.Drawing.Point(59, 79);
            this.account_type_label.Name = "account_type_label";
            this.account_type_label.Size = new System.Drawing.Size(59, 13);
            this.account_type_label.TabIndex = 4;
            this.account_type_label.Text = "Deposit To";
            // 
            // deposit_button
            // 
            this.deposit_button.Location = new System.Drawing.Point(59, 214);
            this.deposit_button.Name = "deposit_button";
            this.deposit_button.Size = new System.Drawing.Size(75, 23);
            this.deposit_button.TabIndex = 5;
            this.deposit_button.Text = "Submit";
            this.deposit_button.UseVisualStyleBackColor = true;
            this.deposit_button.Click += new System.EventHandler(this.deposit_button_Click);
            // 
            // errorProvider1
            // 
            this.errorProvider1.ContainerControl = this;
            // 
            // Deposit_UserControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.Controls.Add(this.deposit_button);
            this.Controls.Add(this.account_type_label);
            this.Controls.Add(this.account_type_dropdown);
            this.Controls.Add(this.amount_deposit_label);
            this.Controls.Add(this.amount_deposit_box);
            this.Name = "Deposit_UserControl";
            this.Title = "Deposit";
            this.Controls.SetChildIndex(this.amount_deposit_box, 0);
            this.Controls.SetChildIndex(this.amount_deposit_label, 0);
            this.Controls.SetChildIndex(this.account_type_dropdown, 0);
            this.Controls.SetChildIndex(this.account_type_label, 0);
            this.Controls.SetChildIndex(this.deposit_button, 0);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label amount_deposit_label;
        private System.Windows.Forms.TextBox amount_deposit_box;
        private System.Windows.Forms.ComboBox account_type_dropdown;
        private System.Windows.Forms.Label account_type_label;
        private System.Windows.Forms.Button deposit_button;
        private System.Windows.Forms.ErrorProvider errorProvider1;
    }
}
