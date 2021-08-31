using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GestDep.Entities
{
    public partial class Enrollment
    {
        public Enrollment()
        {
            Payments = new List<Payment>();
        }
        public Enrollment(DateTime enrollmentDate, Activity activity,
        Payment payment, User user) : this()
        {
            this.CancellationDate = null;
            this.EnrollmentDate = enrollmentDate;
            this.ReturnedFirstCuotaIfCancelledActivity = null;
            //EF se encarga de los atributos ID de tipo int
            this.Activity = activity;
            this.Payments.Add(payment);
            this.User = user;
        }

        public ICollection<int> GetPaymentIds()
        {
            ICollection<int> i = new List<int>();
            foreach (Payment p in this.Payments)
            {
                i.Add(p.Id);
            }
            return i;
        }
        public Payment GetPaymentById(int paymentId)
        {
            foreach (Payment p in this.Payments)
            {
                if (p.Id == paymentId) return p;
            }
            return null;
        }

        public void GetEnrollmentData(out DateTime? cancellationDate, out DateTime enrollmentDate,
            out DateTime? returnedFirstCuotaIfCancelledActivity, out ICollection<int> paymentIds, out string userId)
        {
            cancellationDate = this.CancellationDate; enrollmentDate = this.EnrollmentDate;
            returnedFirstCuotaIfCancelledActivity = this.ReturnedFirstCuotaIfCancelledActivity;
            paymentIds = this.GetPaymentIds(); userId = this.User.Id;
        }
        
    }
}
