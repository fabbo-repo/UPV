using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GestDep.Entities
{
    public partial class Payment
    {
        public Payment() 
        {
        }

        public Payment(DateTime date, string description, double quantity) 
        {
            Date = date;
            Description = description;
            //EF se encarga de los atributos ID de tipo int
            Quantity = quantity;
        }

        public void GetPaymentData(out DateTime date, out string description, out double quantity)
        {
            date = this.Date; description = this.Description; quantity = this.Quantity;
        }
    }
}
