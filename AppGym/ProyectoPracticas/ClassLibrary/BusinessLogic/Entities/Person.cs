using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GestDep.Entities
{
    public partial class Person
    {
        public Person()
        {
        }
        public Person(string address, string iban, string id, string name, int zipCode)
        {
            Address = address;
            IBAN = iban;
            Name = name;
            ZipCode = zipCode;
            Id = id; // //DNI value. It is a String, so EE doesn't manage it.
        }
    }
}
