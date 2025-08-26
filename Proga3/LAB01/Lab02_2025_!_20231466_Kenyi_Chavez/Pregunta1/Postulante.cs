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
			this.paterno= null;
			this.materno= null;
			this.nombre= null;
			this.dni= null; 
		}
		
		public Postulante(string paterno,string materno,string nombre,string dni){
			this.paterno= paterno;
			this.materno= materno;
			this.nombre= nombre;
			this.dni= dni; 
		}
		
		public Postulante(Postulante postulante){
			this.paterno= postulante.Paterno;
			this.materno= postulante.Materno;
			this.nombre= postulante.Nombre;
			this.dni= postulante.ni; 
		}
		
		public override string ToString(){
			return this.paterno + " " + this.materno + " " + this.nombre +
			"(" + this.dni + ")";
		}
	}
}