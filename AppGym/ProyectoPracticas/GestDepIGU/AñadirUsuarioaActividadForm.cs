using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GestDep.Services;
using GestDep.Persistence;

namespace GestDepIGU
{
    public partial class AñadirUsuarioaActividadForm : Form
    {
        private IGestDepService service;
        private int idActv = -1;
        public AñadirUsuarioaActividadForm(IGestDepService service)
        {
            InitializeComponent();
            this.service = service;
            LoadData();
        }

        public void mostrarError() {
            DialogResult answer = MessageBox.Show(this,
                    "No se pudo crear la BD",
                    "Error",
                    MessageBoxButtons.AbortRetryIgnore,
                    MessageBoxIcon.Exclamation);
            if (answer == DialogResult.Retry) { mostrarError();  }
        }

        private void Baceptar_Click(object sender, EventArgs e)
        {
            String dniUsuario = usuario.Text;

            if (idActv != -1)
            {
                service.EnrollUserInActivity(idActv, dniUsuario);
            }
        }

        private void Bcancelar_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        public void LoadData() {
            ICollection<int> activ = service.GetAllActivitiesIds();
            Actividades.Items.Clear();
            if (activ != null) {
                foreach (int i in service.GetAllActivitiesIds())
                    Actividades.Items.Add(i);
                Actividades.SelectedIndex = -1;
                Actividades.ResetText();
            }
        }

        private void Actividades_SelectedIndexChanged(object sender, EventArgs e)
        {
            idActv = (int)Actividades.SelectedItem;
        }
    }
}
