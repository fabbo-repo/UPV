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
using GestDepIGU.SecondaryForms;

namespace GestDepIGU
{
    public partial class GestDepApp : Form
    {
        private IGestDepService service;
        // Caso 1:
        private AddActivity AnyadirActividadForm;
        // Caso 2:
        private AssignInstructor AsignarMonitorForm;
        // Caso 3:
        private EnrollUser InscribirUsuarioForm;
        // Caso 4:
        private AddUser AnyadirUsuarioForm;
        // Caso 5
        private AvailableRooms ListarSalasLibresForm;
        // Formularios adicionales
        private ListActivities ListarActividadesForm;
        
        public GestDepApp(IGestDepService service)
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
            this.service = service;

        }

        private void AnyadirActividad(object sender, EventArgs e)
        {
            this.AnyadirActividadForm = new AddActivity(this.service);
            this.AnyadirActividadForm.ShowDialog();
        }

        private void ListarActividades(object sender, EventArgs e)
        {
            this.ListarActividadesForm = new ListActivities(this.service);
            this.ListarActividadesForm.ShowDialog();
        }

        private void AnyadirMonitorActividad(object sender, EventArgs e)
        {
            this.AsignarMonitorForm = new AssignInstructor(this.service);
            this.AsignarMonitorForm.ShowDialog();
        }

        private void InscribirUsuarioActividad(object sender, EventArgs e)
        {
            this.InscribirUsuarioForm = new EnrollUser(this.service);
            this.InscribirUsuarioForm.ShowDialog();
        }

        private void ListarSalasLibres(object sender, EventArgs e)
        {
            this.ListarSalasLibresForm = new AvailableRooms(this.service);
            this.ListarSalasLibresForm.ShowDialog();
        }

        private void AnyadirUsuario(object sender, EventArgs e)
        {
            this.AnyadirUsuarioForm = new AddUser(this.service);
            this.AnyadirUsuarioForm.ShowDialog();
        }
    }
}
