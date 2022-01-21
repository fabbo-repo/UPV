namespace GestDepIGU
{
    partial class AñadirMonitoraActividadForm
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
            this.BAceptar = new System.Windows.Forms.Button();
            this.Bcancelar = new System.Windows.Forms.Button();
            this.comboActividades = new System.Windows.Forms.ComboBox();
            this.usuario = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // BAceptar
            // 
            this.BAceptar.Location = new System.Drawing.Point(353, 297);
            this.BAceptar.Name = "BAceptar";
            this.BAceptar.Size = new System.Drawing.Size(75, 23);
            this.BAceptar.TabIndex = 0;
            this.BAceptar.Text = "Aceptar";
            this.BAceptar.UseVisualStyleBackColor = true;
            this.BAceptar.Click += new System.EventHandler(this.BAceptar_Click);
            // 
            // Bcancelar
            // 
            this.Bcancelar.Location = new System.Drawing.Point(272, 297);
            this.Bcancelar.Name = "Bcancelar";
            this.Bcancelar.Size = new System.Drawing.Size(75, 23);
            this.Bcancelar.TabIndex = 1;
            this.Bcancelar.Text = "Cancelar";
            this.Bcancelar.UseVisualStyleBackColor = true;
            this.Bcancelar.Click += new System.EventHandler(this.Bcancelar_Click);
            // 
            // comboActividades
            // 
            this.comboActividades.FormattingEnabled = true;
            this.comboActividades.Location = new System.Drawing.Point(193, 132);
            this.comboActividades.Name = "comboActividades";
            this.comboActividades.Size = new System.Drawing.Size(212, 21);
            this.comboActividades.TabIndex = 2;
            this.comboActividades.SelectedIndexChanged += new System.EventHandler(this.comboActividades_SelectedIndexChanged);
            // 
            // usuario
            // 
            this.usuario.Location = new System.Drawing.Point(193, 90);
            this.usuario.Name = "usuario";
            this.usuario.Size = new System.Drawing.Size(212, 20);
            this.usuario.TabIndex = 3;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(82, 90);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(83, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "DNI del usuario:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(85, 139);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(54, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Actividad:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(136, 32);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(129, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Añadir monitor a actividad";
            // 
            // AñadirMonitoraActividadForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(453, 341);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.usuario);
            this.Controls.Add(this.comboActividades);
            this.Controls.Add(this.Bcancelar);
            this.Controls.Add(this.BAceptar);
            this.Name = "AñadirMonitoraActividadForm";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button BAceptar;
        private System.Windows.Forms.Button Bcancelar;
        private System.Windows.Forms.ComboBox comboActividades;
        private System.Windows.Forms.TextBox usuario;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
    }
}