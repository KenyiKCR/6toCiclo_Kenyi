using System;

namespace Pregunta1{
	public class Postulante{
		private string paterno;
		private string materno;
		private string nombre;
		private string dni;
		
		public string Paterno{get{return paterno;} set{paterno = value;}}
		public string Materno{get{return materno;} set{materno = value;}}
		public string Nombre{get{return nombre;} set{nombre = value;}}
		public string Dni{get{return dni;} set{dni = value;}}
		
		public Postulante(){
			this.paterno=null;
			this.materno=null;
			this.dni=null;
			this.nombre=null;
		}
		
		public Postulante(string paterno,string materno, string nombre, string dni){
			this.paterno=paterno;
			this.materno=materno;
			this.dni=dni;
			this.nombre=nombre;
		}
		
		public Postulante(Postulante postulante){
			this.paterno=postulante.paterno;
			this.materno=postulante.materno;
			this.dni=postulante.dni;
			this.nombre=postulante.nombre;	
		}
		
		public override string ToString(){
			return this.Paterno + " " + this.Materno + ", " + this.Nombre + 
			"(" + this.Dni + ")";
		}
	}
}