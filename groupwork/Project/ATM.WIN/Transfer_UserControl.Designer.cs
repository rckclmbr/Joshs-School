namespace ATM.WIN
{
    partial class Transfer_UserControl
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
            this.transfer_from_type_box = new System.Windows.Forms.ComboBox();
            this.transfer_from_type_label = new System.Windows.Forms.Label();
            this.transfer_to_label = new System.Windows.Forms.Label();
            this.transfer_to_account_box = new System.Windows.Forms.ComboBox();
            this.transfer_to_type_box = new System.Windows.Forms.ComboBox();
            this.transfer_amount_textbox = new System.Windows.Forms.TextBox();
            this.transfer_button = new System.Windows.Forms.Button();
            this.transfer_amount_label = new System.Windows.Forms.Label();
            this.errorProvider1 = new System.Windows.Forms.ErrorProvider(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).BeginInit();
            this.SuspendLayout();
            // 
            // transfer_from_type_box
            // 
            this.transfer_from_type_box.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.transfer_from_type_box.FormattingEnabled = true;
            this.transfer_from_type_box.Location = new System.Drawing.Point(55, 91);
            this.transfer_from_type_box.Name = "transfer_from_type_box";
            this.transfer_from_type_box.Size = new System.Drawing.Size(121, 21);
            this.transfer_from_type_box.TabIndex = 1;
            // 
            // transfer_from_type_label
            // 
            this.transfer_from_type_label.AutoSize = true;
            this.transfer_from_type_label.Location = new System.Drawing.Point(52, 75);
            this.transfer_from_type_label.Name = "transfer_from_type_label";
            this.transfer_from_type_label.Size = new System.Drawing.Size(72, 13);
            this.transfer_from_type_label.TabIndex = 2;
            this.transfer_from_type_label.Text = "Transfer From";
            // 
            // transfer_to_label
            // 
            this.transfer_to_label.AutoSize = true;
            this.transfer_to_label.Location = new System.Drawing.Point(52, 119);
            this.transfer_to_label.Name = "transfer_to_label";
            this.transfer_to_label.Size = new System.Drawing.Size(62, 13);
            this.transfer_to_label.TabIndex = 3;
            this.transfer_to_label.Text = "Transfer To";
            // 
            // transfer_to_account_box
            // 
            this.transfer_to_account_box.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.transfer_to_account_box.FormattingEnabled = true;
            this.transfer_to_account_box.Location = new System.Drawing.Point(55, 135);
            this.transfer_to_account_box.Name = "transfer_to_account_box";
            this.transfer_to_account_box.Size = new System.Drawing.Size(121, 21);
            this.transfer_to_account_box.TabIndex = 4;
            this.transfer_to_account_box.SelectedIndexChanged += new System.EventHandler(this.transfer_to_account_box_SelectedIndexChanged);
            // 
            // transfer_to_type_box
            // 
            this.transfer_to_type_box.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.transfer_to_type_box.FormattingEnabled = true;
            this.transfer_to_type_box.Location = new System.Drawing.Point(55, 163);
            this.transfer_to_type_box.Name = "transfer_to_type_box";
            this.transfer_to_type_box.Size = new System.Drawing.Size(121, 21);
            this.transfer_to_type_box.TabIndex = 5;
            // 
            // transfer_amount_textbox
            // 
            this.transfer_amount_textbox.Location = new System.Drawing.Point(58, 207);
            this.transfer_amount_textbox.Name = "transfer_amount_textbox";
            this.transfer_amount_textbox.Size = new System.Drawing.Size(105, 20);
            this.transfer_amount_textbox.TabIndex = 6;
            this.transfer_amount_textbox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // transfer_button
            // 
            this.transfer_button.Location = new System.Drawing.Point(61, 254);
            this.transfer_button.Name = "transfer_button";
            this.transfer_button.Size = new System.Drawing.Size(75, 23);
            this.transfer_button.TabIndex = 7;
            this.transfer_button.Text = "Transfer";
            this.transfer_button.UseVisualStyleBackColor = true;
            this.transfer_button.Click += new System.EventHandler(this.transfer_button_Click);
            // 
            // transfer_amount_label
            // 
            this.transfer_amount_label.AutoSize = true;
            this.transfer_amount_label.Location = new System.Drawing.Point(58, 191);
            this.transfer_amount_label.Name = "transfer_amount_label";
            this.transfer_amount_label.Size = new System.Drawing.Size(43, 13);
            this.transfer_amount_label.TabIndex = 8;
            this.transfer_amount_label.Text = "Amount";
            // 
            // errorProvider1
            // 
            this.errorProvider1.ContainerControl = this;
            // 
            // Transfer_UserControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.Controls.Add(this.transfer_amount_label);
            this.Controls.Add(this.transfer_button);
            this.Controls.Add(this.transfer_amount_textbox);
            this.Controls.Add(this.transfer_to_type_box);
            this.Controls.Add(this.transfer_to_account_box);
            this.Controls.Add(this.transfer_from_type_label);
            this.Controls.Add(this.transfer_to_label);
            this.Controls.Add(this.transfer_from_type_box);
            this.Name = "Transfer_UserControl";
            this.Title = "Transfer";
            this.Controls.SetChildIndex(this.transfer_from_type_box, 0);
            this.Controls.SetChildIndex(this.transfer_to_label, 0);
            this.Controls.SetChildIndex(this.transfer_from_type_label, 0);
            this.Controls.SetChildIndex(this.transfer_to_account_box, 0);
            this.Controls.SetChildIndex(this.transfer_to_type_box, 0);
            this.Controls.SetChildIndex(this.transfer_amount_textbox, 0);
            this.Controls.SetChildIndex(this.transfer_button, 0);
            this.Controls.SetChildIndex(this.transfer_amount_label, 0);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox transfer_from_type_box;
        private System.Windows.Forms.Label transfer_from_type_label;
        private System.Windows.Forms.Label transfer_to_label;
        private System.Windows.Forms.ComboBox transfer_to_account_box;
        private System.Windows.Forms.ComboBox transfer_to_type_box;
        private System.Windows.Forms.TextBox transfer_amount_textbox;
        private System.Windows.Forms.Button transfer_button;
        private System.Windows.Forms.Label transfer_amount_label;
        private System.Windows.Forms.ErrorProvider errorProvider1;

    }
}
