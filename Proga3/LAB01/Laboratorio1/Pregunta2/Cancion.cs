using System.ComponentModel;

namespace Pregunta2{
	public class Cancion{
		private string titulo;
		private string otroTitulo;
		private BindingList<string> interpretes;
		private BindingList<string> compositores;
		private Genero generoMusical;
		private string album;
		private int? opus;
		private int? subOpus;
		private string dedicatoria;
		
		public string Titulo{get{return titulo;} set{this.titulo = value;}}
		public string OtroTitulo{get{return otroTitulo;} set{this.otroTitulo = value;}}
		public Genero? GeneroMusical{get{return generoMusical} set{this.generoMusical = value}}
		public string album{get{return album} set{this.album=value}}
		public int? Opus{get{return opus} set{this.opus=value}}
		public int? SubOpus{get{return subOpus} set{this.subOpus=value}}
		public string Dedicatoria{get{return dedicatoria} set{this.dedicatoria=value}}
		
		public void agregarInterprete(string interprete){
			this.interpretes.Add(interprete);
		}
		
		public void agregarCompositores(string compositor){
			this.compositores.Add(compositor);
		}
		
		public Cancion(){
			this.titulo = null;
			this.otroTitulo = null;
			this.interpretes = new BindingList<string>();
			this.compositores = new BindingList<string>();
			this.generoMusical = null;
			this.album=null;
			this.opus=null;
			this.subOpus=null;
			this.dedicatoria=null;
		}
		
		public override string ToString(){
			string reporte = "TITULO: " + this.titulo + "\n";
			if(otroTitulo!=null)reporte += "TAMBIEN CONOCIDA COMO: " + this.otroTitulo + "\n";
			if(this.interpretes.Count > 0){
				reporte += "INTERORETADO POR: ";
				for(int i=0;i<this.interpretes.Count;i++){
					if(i>0) 
						reporte += ", ";
					reporte += interpretes[i];
				}					
				reporte += "\n";
			}
			if(this.compositores.Count > 0){
				reporte += "COMPUESTO POR: ";
				for(int i=0;i<this.compositores.Count;i++){
					if(i>0) 
						reporte += ", ";
					reporte += compositores[i];
				}					
				reporte += "\n";
			}
			reporte += "TIPO: ";
			switch(this.GeneroMusical){
				case Genero.FOLKLORE:
				reporte += "Folklore";
				break;
				case Genero.CLASICA:
				reporte += "Clásica";
				break;
			}
			reporte += "\n OPUS: "+ this.Opus + " SUBOPUS: " + this.subOpus + "\n";
			reporte += "DEDICADO A: "+ this.dedicatoria + "\n";
		}
	}
}