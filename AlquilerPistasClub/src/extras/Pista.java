/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package extras;

import javafx.beans.property.StringProperty;
import javafx.beans.property.SimpleStringProperty;

/**
 *
 * @author Fabianno
 */
public class Pista {
    
    private final StringProperty duracion = new SimpleStringProperty();
    
    private final StringProperty court = new SimpleStringProperty();
    
    private final StringProperty horaIni = new SimpleStringProperty();
    
    public Pista(String court, String duracion, String horaIni) {
        this.court.setValue(court);
        this.horaIni.setValue(horaIni);
        this.duracion.setValue(duracion);
    }
    
   public final StringProperty courtProperty() {
	return this.court;
    }
    public final java.lang.String getCourt() {
	return this.courtProperty().get();
    }
    public final void setCourt(final java.lang.String court) {
	this.courtProperty().set(court);
    }
    
    public final StringProperty horaIniProperty() {
	return this.horaIni;
    }
    public final java.lang.String getHoraIni() {
	return this.horaIniProperty().get();
    }
    public final void setHoraIni(final java.lang.String horaIni) {
	this.horaIniProperty().set(horaIni);
    }
    
    public final StringProperty duracionProperty() {
	return this.duracion;
    }
    public final java.lang.String getDuracion() {
	return this.duracionProperty().get();
    }
    public final void setDuracion(final java.lang.String duracion) {
	this.duracionProperty().set(duracion);
    }
}
