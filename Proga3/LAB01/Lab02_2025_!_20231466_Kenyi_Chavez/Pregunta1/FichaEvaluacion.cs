using System;

namespace Pregunta1{
	public class FichaEvaluacion{
		private Postulante candidato;
		private DateTime? fecha_hora;
		private int? evaluacion_expediente;
		private int? evaluacion_entrevista;
		private int? evaluacion_examen;
		private Estado estado_candidato;
		
		public Postulante Candidato{get{return candidato;}set{candidato  = value;}}
		public DateTime? Fecha_hora{get{return fecha_hora;}set{fecha_hora  = value;}}
		public int? Evaluacion_expediente{get{return evaluacion_expediente;}set{evaluacion_expediente  = value;}}
		public int? Evaluacion_entrevista{get{return evaluacion_entrevista;}set{evaluacion_entrevista  = value;}}
		public int? Evaluacion_examen{get{return evaluacion_examen;}set{evaluacion_examen  = value;}}
		public Estado Estado_candidato{
			get{
				int? suma = this.Evaluacion_entrevista + this.Evaluacion_examen + this.Evaluacion_expediente;
				if(suma>75){
					this.estado_candidato=Estado.ADMITIDO;	
				}
				else this.estado_candidato=Estado.NO_ADMITIDO;
				
				return estado_candidato;
			}
			set{estado_candidato = value;}
		}
		
		public FichaEvaluacion(){
			this.candidato = null;
			this.fecha_hora = null;
			this.evaluacion_entrevista = null;
			this.evaluacion_examen = null;
			this.evaluacion_expediente = null;
			this.estado_candidato = Estado.SIN_EVALUACIÓN;
		}
		
		public FichaEvaluacion(Postulante candidato, DateTime fecha_hora, int evaluacion_entrevista, int evaluacion_examen, int evaluacion_expediente, Estado estado_candidato){
			Postulante candidatoCopia = new Postulante(candidato);
			this.candidato = candidatoCopia;
			this.fecha_hora = fecha_hora;
			this.evaluacion_entrevista = evaluacion_entrevista;
			this.evaluacion_examen = evaluacion_examen;
			this.evaluacion_expediente = evaluacion_expediente;
			this.estado_candidato = estado_candidato;
		}
		
		public FichaEvaluacion(FichaEvaluacion fichaEvaluacion){
			Postulante candidatoCopia = new Postulante(fichaEvaluacion.Candidato);
			this.candidato = candidatoCopia;
			this.fecha_hora = fichaEvaluacion.Fecha_hora;
			this.evaluacion_entrevista = fichaEvaluacion.Evaluacion_entrevista;
			this.evaluacion_examen = fichaEvaluacion.Evaluacion_examen;
			this.evaluacion_expediente = fichaEvaluacion.Evaluacion_expediente;
			this.estado_candidato = fichaEvaluacion.Estado_candidato;
		}
	}
}
