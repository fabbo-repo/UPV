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
public class ReservaT {

    private final StringProperty num = new SimpleStringProperty();
    
    private final StringProperty day = new SimpleStringProperty();
    
    private final StringProperty court = new SimpleStringProperty();
    
    private final StringProperty horaIni = new SimpleStringProperty();
    
    private final StringProperty horaFin = new SimpleStringProperty();
    
    private final StringProperty paid = new SimpleStringProperty();
    
    public ReservaT(String num, String day, String court, String horaIni, String horaFin, String paid) {
        this.num.setValue(num);
        this.day.setValue(day);
        this.court.setValue(court);
        this.horaIni.setValue(horaIni);
        this.horaFin.setValue(horaFin);
        this.paid.setValue(paid);
    }
    
    public final StringProperty numProperty() {
		return this.num;
	}
    public final java.lang.String getNum() {
	return this.numProperty().get();
    }
    public final void setNum(final java.lang.String num) {
	this.numProperty().set(num);
    }
    
    public final StringProperty dayProperty() {
	return this.day;
    }
    public final java.lang.String getDay() {
	return this.dayProperty().get();
    }
    public final void setDay(final java.lang.String day) {
	this.dayProperty().set(day);
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
    
    public final StringProperty horaFinProperty() {
	return this.horaFin;
    }
    public final java.lang.String getHoraFin() {
	return this.horaFinProperty().get();
    }
    public final void setHoraFin(final java.lang.String horaFin) {
	this.horaFinProperty().set(horaFin);
    }
    
    public final StringProperty paidProperty() {
	return this.paid;
    }
    public final java.lang.String getPaid() {
	return this.paidProperty().get();
    }
    public final void setPaid(final java.lang.String paid) {
	this.paidProperty().set(paid);
    }
}