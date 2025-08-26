using System.ComponentModel;

namespace Pregunta1
{
	public class Admision
	{
		private BindingList<FichaEvaluacion> listaFicha;
		private int cantidad_admitidos;
		private int cantidad_postulantes;
		
		public Admision(){
			this.listaFicha = new BindingList<FichaEvaluacion>();
			this.cantidad_admitidos = 0;
			this.cantidad_postulantes = 0;
		}
		
		public void agregarFichaDeEvaluacion(FichaEvaluacion ficha){
			FichaEvaluacion fichaCopia = new FichaEvaluacion(ficha);
			this.listaFicha.Add(fichaCopia);
			this.cantidad_postulantes++;
			if(ficha.Estado_candidato == Estado.ADMITIDO)
				this.cantidad_admitidos++;
		}
		
		public override string ToString(){
			string reporte = "PROCESO DE ADIMISION: ";
			reporte += this.cantidad_postulantes + "postulantes, " + 
			this.cantidad_admitidos + " admitidos\n";
			reporte += "\t LISTA DE ADMITIDOS:\n";
			foreach(FichaEvaluacion ficha in listaFicha){
				if(ficha.Estado_candidato == Estado.ADMITIDO){
					reporte += "\t\t" + ficha.Candidato + "\n";
				}
			}
			return reporte;
		}
	}
}