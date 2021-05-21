
namespace GestDepIGU
{
    partial class GestDepApp
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(GestDepApp));
            this.optionMenu = new System.Windows.Forms.MenuStrip();
            this.actividadesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.añadirActividadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.listarActividadesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.añadirContenedoresToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.inscribirUsuarioAActividadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.salasToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.listarSalasLibresToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.usuariosToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.añadirUsuarioToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.optionMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // optionMenu
            // 
            this.optionMenu.BackColor = System.Drawing.Color.DarkGray;
            resources.ApplyResources(this.optionMenu, "optionMenu");
            this.optionMenu.GripStyle = System.Windows.Forms.ToolStripGripStyle.Visible;
            this.optionMenu.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.optionMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.actividadesToolStripMenuItem,
            this.salasToolStripMenuItem,
            this.usuariosToolStripMenuItem});
            this.optionMenu.Name = "optionMenu";
            // 
            // actividadesToolStripMenuItem
            // 
            this.actividadesToolStripMenuItem.BackColor = System.Drawing.Color.Gainsboro;
            this.actividadesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.añadirActividadToolStripMenuItem,
            this.listarActividadesToolStripMenuItem,
            this.añadirContenedoresToolStripMenuItem,
            this.inscribirUsuarioAActividadToolStripMenuItem});
            this.actividadesToolStripMenuItem.Name = "actividadesToolStripMenuItem";
            resources.ApplyResources(this.actividadesToolStripMenuItem, "actividadesToolStripMenuItem");
            // 
            // añadirActividadToolStripMenuItem
            // 
            this.añadirActividadToolStripMenuItem.BackColor = System.Drawing.SystemColors.ControlLight;
            this.añadirActividadToolStripMenuItem.Name = "añadirActividadToolStripMenuItem";
            resources.ApplyResources(this.añadirActividadToolStripMenuItem, "añadirActividadToolStripMenuItem");
            this.añadirActividadToolStripMenuItem.Click += new System.EventHandler(this.AnyadirActividad);
            // 
            // listarActividadesToolStripMenuItem
            // 
            this.listarActividadesToolStripMenuItem.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.listarActividadesToolStripMenuItem.Name = "listarActividadesToolStripMenuItem";
            resources.ApplyResources(this.listarActividadesToolStripMenuItem, "listarActividadesToolStripMenuItem");
            this.listarActividadesToolStripMenuItem.Click += new System.EventHandler(this.ListarActividades);
            // 
            // añadirContenedoresToolStripMenuItem
            // 
            this.añadirContenedoresToolStripMenuItem.BackColor = System.Drawing.SystemColors.ControlLight;
            this.añadirContenedoresToolStripMenuItem.Name = "añadirContenedoresToolStripMenuItem";
            resources.ApplyResources(this.añadirContenedoresToolStripMenuItem, "añadirContenedoresToolStripMenuItem");
            this.añadirContenedoresToolStripMenuItem.Click += new System.EventHandler(this.AnyadirMonitorActividad);
            // 
            // inscribirUsuarioAActividadToolStripMenuItem
            // 
            this.inscribirUsuarioAActividadToolStripMenuItem.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.inscribirUsuarioAActividadToolStripMenuItem.Name = "inscribirUsuarioAActividadToolStripMenuItem";
            resources.ApplyResources(this.inscribirUsuarioAActividadToolStripMenuItem, "inscribirUsuarioAActividadToolStripMenuItem");
            this.inscribirUsuarioAActividadToolStripMenuItem.Click += new System.EventHandler(this.InscribirUsuarioActividad);
            // 
            // salasToolStripMenuItem
            // 
            this.salasToolStripMenuItem.BackColor = System.Drawing.Color.Gainsboro;
            this.salasToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.listarSalasLibresToolStripMenuItem});
            this.salasToolStripMenuItem.Name = "salasToolStripMenuItem";
            resources.ApplyResources(this.salasToolStripMenuItem, "salasToolStripMenuItem");
            // 
            // listarSalasLibresToolStripMenuItem
            // 
            this.listarSalasLibresToolStripMenuItem.BackColor = System.Drawing.SystemColors.ControlLight;
            this.listarSalasLibresToolStripMenuItem.Name = "listarSalasLibresToolStripMenuItem";
            resources.ApplyResources(this.listarSalasLibresToolStripMenuItem, "listarSalasLibresToolStripMenuItem");
            this.listarSalasLibresToolStripMenuItem.Click += new System.EventHandler(this.ListarSalasLibres);
            // 
            // usuariosToolStripMenuItem
            // 
            this.usuariosToolStripMenuItem.BackColor = System.Drawing.Color.Gainsboro;
            this.usuariosToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.añadirUsuarioToolStripMenuItem});
            this.usuariosToolStripMenuItem.Name = "usuariosToolStripMenuItem";
            resources.ApplyResources(this.usuariosToolStripMenuItem, "usuariosToolStripMenuItem");
            // 
            // añadirUsuarioToolStripMenuItem
            // 
            this.añadirUsuarioToolStripMenuItem.BackColor = System.Drawing.SystemColors.ControlLight;
            this.añadirUsuarioToolStripMenuItem.Name = "añadirUsuarioToolStripMenuItem";
            resources.ApplyResources(this.añadirUsuarioToolStripMenuItem, "añadirUsuarioToolStripMenuItem");
            this.añadirUsuarioToolStripMenuItem.Click += new System.EventHandler(this.AnyadirUsuario);
            // 
            // GestDepApp
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Window;
            this.Controls.Add(this.optionMenu);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MainMenuStrip = this.optionMenu;
            this.MaximizeBox = false;
            this.Name = "GestDepApp";
            this.optionMenu.ResumeLayout(false);
            this.optionMenu.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip optionMenu;
        private System.Windows.Forms.ToolStripMenuItem actividadesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem añadirActividadToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem listarActividadesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem añadirContenedoresToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem inscribirUsuarioAActividadToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem salasToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem listarSalasLibresToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem usuariosToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem añadirUsuarioToolStripMenuItem;
    }
}

