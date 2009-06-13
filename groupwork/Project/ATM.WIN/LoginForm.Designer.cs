namespace ATM.WIN
{
    partial class LoginForm
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
            this.acctnum_textbox = new System.Windows.Forms.TextBox();
            this.pin_textbox = new System.Windows.Forms.TextBox();
            this.acctnum_label = new System.Windows.Forms.Label();
            this.pin_label = new System.Windows.Forms.Label();
            this.login_button = new System.Windows.Forms.Button();
            this.Error_Label = new System.Windows.Forms.Label();
            this.errorProvider1 = new System.Windows.Forms.ErrorProvider(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).BeginInit();
            this.SuspendLayout();
            // 
            // acctnum_textbox
            // 
            this.acctnum_textbox.Location = new System.Drawing.Point(86, 95);
            this.acctnum_textbox.Name = "acctnum_textbox";
            this.acctnum_textbox.Size = new System.Drawing.Size(100, 20);
            this.acctnum_textbox.TabIndex = 0;
            // 
            // pin_textbox
            // 
            this.pin_textbox.Location = new System.Drawing.Point(86, 146);
            this.pin_textbox.MaxLength = 4;
            this.pin_textbox.Name = "pin_textbox";
            this.pin_textbox.PasswordChar = '*';
            this.pin_textbox.Size = new System.Drawing.Size(100, 20);
            this.pin_textbox.TabIndex = 1;
            // 
            // acctnum_label
            // 
            this.acctnum_label.AutoSize = true;
            this.acctnum_label.Location = new System.Drawing.Point(86, 76);
            this.acctnum_label.MaximumSize = new System.Drawing.Size(100, 20);
            this.acctnum_label.Name = "acctnum_label";
            this.acctnum_label.Size = new System.Drawing.Size(87, 13);
            this.acctnum_label.TabIndex = 2;
            this.acctnum_label.Text = "Account Number";
            // 
            // pin_label
            // 
            this.pin_label.AutoSize = true;
            this.pin_label.Location = new System.Drawing.Point(86, 127);
            this.pin_label.Name = "pin_label";
            this.pin_label.Size = new System.Drawing.Size(25, 13);
            this.pin_label.TabIndex = 3;
            this.pin_label.Text = "PIN";
            // 
            // login_button
            // 
            this.login_button.Location = new System.Drawing.Point(98, 190);
            this.login_button.Name = "login_button";
            this.login_button.Size = new System.Drawing.Size(75, 23);
            this.login_button.TabIndex = 4;
            this.login_button.Text = "Login";
            this.login_button.UseVisualStyleBackColor = true;
            this.login_button.Click += new System.EventHandler(this.login_button_Click);
            // 
            // Error_Label
            // 
            this.Error_Label.AutoSize = true;
            this.Error_Label.ForeColor = System.Drawing.Color.Red;
            this.Error_Label.Location = new System.Drawing.Point(100, 241);
            this.Error_Label.Name = "Error_Label";
            this.Error_Label.Size = new System.Drawing.Size(0, 13);
            this.Error_Label.TabIndex = 5;
            // 
            // errorProvider1
            // 
            this.errorProvider1.ContainerControl = this;
            // 
            // LoginForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 273);
            this.Controls.Add(this.Error_Label);
            this.Controls.Add(this.login_button);
            this.Controls.Add(this.pin_label);
            this.Controls.Add(this.acctnum_label);
            this.Controls.Add(this.pin_textbox);
            this.Controls.Add(this.acctnum_textbox);
            this.Name = "LoginForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "ATM";
            this.Load += new System.EventHandler(this.LoginForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox acctnum_textbox;
        private System.Windows.Forms.TextBox pin_textbox;
        private System.Windows.Forms.Label acctnum_label;
        private System.Windows.Forms.Label pin_label;
        private System.Windows.Forms.Button login_button;
        private System.Windows.Forms.Label Error_Label;
        private System.Windows.Forms.ErrorProvider errorProvider1;
    }
}

