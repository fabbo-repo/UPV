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
    public partial class AñadirMonitoraActividadForm : Form
    {
        private IGestDepService service;
        private int idActv = -1;
        public AñadirMonitoraActividadForm(IGestDepService service)
        {
            InitializeComponent();
            this.service = service;
            LoadData();
        }

        private void BAceptar_Click(object sender, EventArgs e)
        {
            String dniUsuario = usuario.Text;

            if (idActv != -1)
            {
                service.AssignInstructorToActivity(idActv, dniUsuario);
            }
        }

        private void Bcancelar_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
        public void LoadData()
        {
            ICollection<int> activ = service.GetAllActivitiesIds();
            comboActividades.Items.Clear();
            if (activ != null)
            {
                foreach (int i in service.GetAllActivitiesIds())
                    comboActividades.Items.Add(i);
                comboActividades.SelectedIndex = -1;
                comboActividades.ResetText();
            }
        }

        private void comboActividades_SelectedIndexChanged(object sender, EventArgs e)
        {
            idActv = (int)Actividades.SelectedItem;
        }
    }
}
