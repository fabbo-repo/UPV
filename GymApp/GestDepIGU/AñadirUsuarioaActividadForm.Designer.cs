namespace GestDepIGU
{
    partial class AñadirUsuarioaActividadForm
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
            this.Baceptar = new System.Windows.Forms.Button();
            this.Bcancelar = new System.Windows.Forms.Button();
            this.Actividades = new System.Windows.Forms.ComboBox();
            this.usuario = new System.Windows.Forms.TextBox();
            this.titulo = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // Baceptar
            // 
            this.Baceptar.Location = new System.Drawing.Point(356, 298);
            this.Baceptar.Name = "Baceptar";
            this.Baceptar.Size = new System.Drawing.Size(75, 23);
            this.Baceptar.TabIndex = 0;
            this.Baceptar.Text = "Aceptar";
            this.Baceptar.UseVisualStyleBackColor = true;
            this.Baceptar.Click += new System.EventHandler(this.Baceptar_Click);
            // 
            // Bcancelar
            // 
            this.Bcancelar.Location = new System.Drawing.Point(275, 298);
            this.Bcancelar.Name = "Bcancelar";
            this.Bcancelar.Size = new System.Drawing.Size(75, 23);
            this.Bcancelar.TabIndex = 1;
            this.Bcancelar.Text = "Cancelar";
            this.Bcancelar.UseVisualStyleBackColor = true;
            this.Bcancelar.Click += new System.EventHandler(this.Bcancelar_Click);
            // 
            // Actividades
            // 
            this.Actividades.FormattingEnabled = true;
            this.Actividades.Location = new System.Drawing.Point(180, 127);
            this.Actividades.Name = "Actividades";
            this.Actividades.Size = new System.Drawing.Size(233, 21);
            this.Actividades.TabIndex = 2;
            this.Actividades.SelectedIndexChanged += new System.EventHandler(this.Actividades_SelectedIndexChanged);
            // 
            // usuario
            // 
            this.usuario.Location = new System.Drawing.Point(180, 93);
            this.usuario.Name = "usuario";
            this.usuario.Size = new System.Drawing.Size(233, 20);
            this.usuario.TabIndex = 3;
            // 
            // titulo
            // 
            this.titulo.AutoSize = true;
            this.titulo.Location = new System.Drawing.Point(91, 29);
            this.titulo.Name = "titulo";
            this.titulo.Size = new System.Drawing.Size(129, 13);
            this.titulo.TabIndex = 5;
            this.titulo.Text = "Añadir usuario a actividad";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(78, 130);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(54, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Acitvidad:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(78, 93);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(83, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "DNI del usuario:";
            // 
            // AñadirUsuarioaActividadForm
            // 
            this.ClientSize = new System.Drawing.Size(452, 346);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.titulo);
            this.Controls.Add(this.usuario);
            this.Controls.Add(this.Actividades);
            this.Controls.Add(this.Bcancelar);
            this.Controls.Add(this.Baceptar);
            this.Name = "AñadirUsuarioaActividadForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button aceptar;
        private System.Windows.Forms.Button Baceptar;
        private System.Windows.Forms.Button Bcancelar;
        private System.Windows.Forms.ComboBox Actividades;
        private System.Windows.Forms.TextBox usuario;
        private System.Windows.Forms.Label titulo;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}