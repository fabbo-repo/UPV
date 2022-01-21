/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controlador_auxiliar;

import DBAcess.ClubDBAccess;
import java.net.URL;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.ResourceBundle;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.layout.TilePane;
import model.Booking;
import model.Court;
import model.Member;

/**
 * FXML Controller class
 *
 * @author Fabianno
 */
public class VistaFormularioReservar implements Initializable {

    @FXML
    private TilePane pane;
    @FXML
    private ComboBox<String> courtChooser;
    @FXML
    private ComboBox<String> hourChooser;
    
    private ClubDBAccess clubPadelData;
    
    private Court court;
    
    private Member member;
    
    private LocalTime hour;
    
    private LocalDate actDate;
    @FXML
    private Button reservarButton;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        reservarButton.setDisable(true);
    }    

    @FXML
    private void courtHandler(ActionEvent event) {
        this.court = new Court(courtChooser.getValue());
        if(this.court!=null && this.hour!=null){reservarButton.setDisable(false);}
    }

    @FXML
    private void hourHandler(ActionEvent event) {
        String ho = hourChooser.getValue();
        this.hour = LocalTime.of(Integer.parseInt(ho.substring(0, 2)), Integer.parseInt(ho.substring(3, 5)));
        if(this.court!=null && this.hour!=null){reservarButton.setDisable(false);}
    }

    @FXML
    private void reservarHandler(ActionEvent event) {
        if((isToday()&&isHourFine(this.hour))||(!isToday())){
            if(!courtHourIsReservedByUser(this.court,this.hour)){
                if(!isCourtFull(court.getName())){
                    if(!hourIsReservedByUser(hour)){
                        boolean paid = this.clubPadelData.hasCreditCard(this.member.getLogin());
                        LocalDateTime ldt = LocalDateTime.now();
                        this.clubPadelData.getBookings().add(
                                        new Booking(ldt,actDate,hour,paid,this.court,this.member));
                        ((Button) event.getSource()).getScene().getWindow().hide();
                    }
                    else{
                        Alert alert = new Alert(Alert.AlertType.INFORMATION);
                        alert.setTitle(clubPadelData.getClubName());
                        alert.setHeaderText("Horario reservado");
                        alert.setContentText("Ya has reservado este horario");
                        alert.show();
                    }
                }
                else{
                    Alert alert = new Alert(Alert.AlertType.INFORMATION);
                    alert.setTitle(clubPadelData.getClubName());
                    alert.setHeaderText("Pista reservada");
                    alert.setContentText("La pista seleccionada está reservada por favor escoge otra pista");
                    alert.show();
                }
            }
            else{
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle(clubPadelData.getClubName());
                alert.setHeaderText("Horario reservado");
                alert.setContentText("Este horario está reservado por favor escoge otro");
                alert.show();
            }
        }
        else{
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle(clubPadelData.getClubName());
            alert.setHeaderText("No se puede reservar");
            alert.setContentText("Solo puede realizar reservas para hoy a partir de la hora actual");
            alert.show();
        }            
    }
    
    @FXML
    private void cancelHandler(ActionEvent event) {
        ((Button) event.getSource()).getScene().getWindow().hide();
    }
    
    public void setDataBaseNMember(ClubDBAccess club,Member m) throws Exception{
        this.clubPadelData=club;
        this.member=m;
    }
    
    /**
     * Verifica que la pista no este llena de reservas
     * @param p
     * @return 
    */ 
    public boolean isCourtFull(String p){
        ArrayList<Booking> reservas = clubPadelData.getCourtBookings(p,actDate);
        return reservas.size()>= clubPadelData.getClubBookingSlots();
    }
    
    public boolean hourIsReservedByUser(LocalTime ls){
        LocalTime lt = ls;
        ArrayList<Booking> ab = clubPadelData.getForDayBookings(actDate);
        for(int i = 0; i < ab.size(); i++){
            if(ab.get(i).getMember().getLogin().equals(this.member.getLogin())){
                if(ab.get(i).getFromTime().equals(lt)){return true;}
            }
        }
        return false;
    }
    
    private boolean isToday(){
        return actDate.equals(LocalDate.now());
    }
    
    private boolean isHourFine(LocalTime h){
        return LocalTime.now().compareTo(h)<0;
    }
    
    private boolean courtHourIsReservedByUser(Court c,LocalTime ls){
        LocalTime lt = ls;
        ArrayList<Booking> ab = clubPadelData.getForDayBookings(actDate);
        for(int i = 0; i < ab.size(); i++){
            if(ab.get(i).getCourt().getName().equals(c.getName())){
                if(ab.get(i).getFromTime().equals(lt)){return true;}
            }
        }
        return false;
    }
    
    public void setDate(LocalDate da){
        this.actDate = da;
        updateBoxes();
    }
    
    private void updateBoxes(){
        ObservableList<String> itemsC = FXCollections.observableArrayList();
        for(int i = 0; i < this.clubPadelData.getCourts().size(); i++){
            itemsC.add(this.clubPadelData.getCourts().get(i).getName());
        }
        courtChooser.setItems(itemsC);
        
        ObservableList<String> itemsH = FXCollections.observableArrayList();
        LocalTime h1 = LocalTime.of(9, 0); int j = 540;
        LocalTime h2;
        
        for(int i = 0; i < this.clubPadelData.getClubBookingSlots()
                && j<1365-this.clubPadelData.getClubBookingDuration(); i++){
            
            String horaIni = h1.toString().substring(0,5);
            h2 = h1.plusMinutes(this.clubPadelData.getClubBookingDuration());
            String horaFin = h2.toString().substring(0,5);
            
            if(isToday()&&isHourFine(h1)){//En caso de que sea hoy la reserva hay que ver la hora
                itemsH.add(horaIni+"-"+horaFin);
            }
            else if(!isToday()){//Si no es hoy hay que ver si ya está ocupado ese horario
                itemsH.add(horaIni+"-"+horaFin);
            }
            
            h1 = h1.plusMinutes(this.clubPadelData.getClubBookingDuration());
            
            j+=this.clubPadelData.getClubBookingDuration();
        }
        hourChooser.setItems(itemsH);
        
    }
}
