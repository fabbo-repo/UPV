/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controlador;

import DBAcess.ClubDBAccess;
import model.Member;
import extras.ReservaT;
import java.net.URL;
import java.time.LocalDate;
import java.time.LocalTime;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.ResourceBundle;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;
import model.Booking;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;

/**
 * FXML Controller class
 *
 * @author Fabianno
 */
public class VistaReservasController implements Initializable {

    
    private ClubDBAccess clubPadelData;
    
    private LocalDate actDate;
    
    private Member member;
    
    private ObservableList datos;
    @FXML
    private Button eraseButton;
    @FXML
    private TableView<ReservaT> tableView;
    @FXML
    private TableColumn<ReservaT, String> columnN;
    @FXML
    private TableColumn<ReservaT, String> columnDay;
    @FXML
    private TableColumn<ReservaT, String> columnIni;
    @FXML
    private TableColumn<ReservaT, String> columnFin;
    @FXML
    private TableColumn<ReservaT, String> columnPaid;
    @FXML
    private TableColumn<ReservaT, String> columnCourt;
    @FXML
    private TextArea infpanel;
    @FXML
    private TextArea instpanel;
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        eraseButton.setDisable(true);
        this.tableView.focusedProperty().addListener(new ChangeListener<Boolean>(){
            @Override
            public void changed(ObservableValue<? extends Boolean> observable, Boolean oldValue,
                                                Boolean newValue) {
		if (tableView.isFocused()) {
                    eraseButton.setDisable(false);
		}
                else{
                    eraseButton.setDisable(true);
                }
            }
	});
        this.tableView.setPlaceholder(new Label("No has realizado una reserva"));
    }    
    
    public void setDataBaseNMember(ClubDBAccess club,Member m) throws Exception{
        this.clubPadelData=club;
        this.member=m;
        updatePistas();
        
    }
    
    public void setDate(LocalDate d) throws Exception{
        actDate=d;
        
    }
    
    private void updatePistas() throws Exception{
        ArrayList<ReservaT> misdatos = new ArrayList<>();
	this.datos = FXCollections.observableList(misdatos);
	
        columnN.setCellValueFactory(new PropertyValueFactory<>("num"));
        columnDay.setCellValueFactory(new PropertyValueFactory<>("day"));
        columnCourt.setCellValueFactory(new PropertyValueFactory<>("court"));
        columnIni.setCellValueFactory(new PropertyValueFactory<>("horaIni"));
        columnFin.setCellValueFactory(new PropertyValueFactory<>("horaFin"));
        columnPaid.setCellValueFactory(new PropertyValueFactory<>("paid"));
        this.tableView.setItems(datos);
        
        ArrayList<Booking> reservasT = clubPadelData.getUserBookings(this.member.getLogin());
        int duracionM = clubPadelData.getClubBookingDuration();
        
        Collections.sort(reservasT, new Comparator<Booking>() {
            public int compare(Booking res1, Booking res2) {
                return res1.getBookingDate().compareTo(res2.getBookingDate());
            }
        });
        
        for(int j = 0; j < reservasT.size() && j < 10; j++){
            int i = reservasT.size()-1 - j;
            String num = ""+(j+1);
            String diaReservado = reservasT.get(i).getMadeForDay().format(DateTimeFormatter.ofPattern("dd-MM-yyyy"));
            String pista = reservasT.get(i).getCourt().getName();
            String horaIni = reservasT.get(i).getFromTime().toString().substring(0,5);
            String horaFin = reservasT.get(i).getFromTime().plusMinutes(duracionM).toString().substring(0,5);
            String paid;
            if(reservasT.get(i).getPaid()) paid = "Pagado";
            else  paid = "No pagado";
            if(reservasT.get(i).getMadeForDay().compareTo(LocalDate.now())>=0){
                datos.add(new ReservaT(num,diaReservado, pista,horaIni,horaFin,paid));
            }
        }
    }
    
    @FXML
    private void erase(ActionEvent event) {
        int i = tableView.getSelectionModel().getSelectedIndex();
        if (i>=0){
            ArrayList<Booking> reservasT = clubPadelData.getUserBookings(this.member.getLogin());
            Collections.sort(reservasT, new Comparator<Booking>() {
                public int compare(Booking res1, Booking res2) {
                    return res1.getBookingDate().compareTo(res2.getBookingDate());
                }
            });
            LocalDate bookingday = reservasT.get(reservasT.size()-i-1).getMadeForDay();
            LocalTime bookingtime = reservasT.get(reservasT.size()-i-1).getFromTime();
            LocalDateTime bookingdaytime = bookingday.atTime(bookingtime.getHour(),bookingtime.getMinute());
            LocalDateTime now = LocalDateTime.now();
            boolean posible = bookingdaytime.isAfter(now.plusDays(1));
            boolean erase = false;
            
            if(posible){erase = true;}
            else{
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle(clubPadelData.getClubName());
                alert.setHeaderText("No se puede eliminar");
                alert.setContentText("La pista seleccionada no se puede eliminar");
                alert.show();
            }
            
            if(erase){
                this.clubPadelData.getBookings().remove(reservasT.get(reservasT.size()-i-1));
                datos.remove(i);
            }
        }
    }

    @FXML
    private void mouseOutInf(MouseEvent event) {
        infpanel.setVisible(false);
    }

    @FXML
    private void mouseOverInf(MouseEvent event) {
        infpanel.setVisible(true);
    }

    @FXML
    private void mouseOutInst(MouseEvent event) {
        instpanel.setVisible(false);
    }

    @FXML
    private void mouseOverInst(MouseEvent event) {
        instpanel.setVisible(true);
    }
    
}
