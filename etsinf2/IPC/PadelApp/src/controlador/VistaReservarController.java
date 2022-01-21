/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controlador;

import DBAcess.ClubDBAccess;
import controlador_auxiliar.VistaFormularioReservar;
import extras.Pista;
import java.net.URL;
import java.time.LocalDate;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.ResourceBundle;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.DateCell;
import javafx.scene.control.DatePicker;
import javafx.scene.control.Label;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.scene.text.Font;
import model.Booking;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.TextArea;
import javafx.scene.image.Image;
import javafx.scene.input.MouseEvent;
import javafx.stage.Modality;
import javafx.stage.Stage;
import model.Member;

/**
 * FXML Controller class
 *
 * @author Fabianno
 */
public class VistaReservarController implements Initializable {

    private ClubDBAccess clubPadelData;
    
    private Member member;
    
    private LocalDate actDate;
    @FXML
    private TabPane tabPane;
    @FXML
    private DatePicker datePicker;
    @FXML
    private TextArea instpanel;
    @FXML
    private TextArea infpanel;
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        this.tabPane.setStyle("-fx-background-color: rgb(220,220,220);");
        datePicker.setDayCellFactory((DatePicker picker) -> {
            return new DateCell() {
                @Override
                public void updateItem(LocalDate date, boolean empty) {
                    super.updateItem(date, empty);
                    LocalDate today = LocalDate.now();
                    setDisable(empty || date.compareTo(today) < 0 );
                }
            };
        });
        actDate=LocalDate.now();
    }    
    
    public void setDataBaseNMember(ClubDBAccess club,Member m) throws Exception{
        this.clubPadelData=club;
        this.member=m;
        updatePistas();
    }
    
    private void updatePistas() throws Exception{
        for(int i = 0; i < clubPadelData.getCourts().size(); i++){
            
            this.tabPane.getTabs().add(
                    new Tab(clubPadelData.getCourts().get(i).getName(),createHorario(i)));
            
        }
    }
    
    @FXML
    private void dataPicked(ActionEvent event) throws Exception{
        actDate = datePicker.getValue();
        eraseTabs();
        updatePistas();
    }
    
    public AnchorPane createHorario(int i){
        AnchorPane anchorPane = new AnchorPane();
        anchorPane.setMaxSize(Double.MAX_VALUE,Double.MAX_VALUE);
        
        ArrayList<Pista> misdatos = new ArrayList<>();
        
	ObservableList datos = FXCollections.observableArrayList(misdatos);
	
        TableView<Pista> horarios = new TableView<>();
        horarios.setPrefSize(TableView.USE_COMPUTED_SIZE, TableView.USE_COMPUTED_SIZE);
        horarios.setPlaceholder(new Label("No hay reservas para esta pista"));
        
        TableColumn<Pista,String> t1 = new TableColumn<>("Hora inicio:");
        TableColumn<Pista,String> t2 = new TableColumn<>("Duración:");
        TableColumn<Pista,String> t3 = new TableColumn<>("Reservada por:");
        t1.setCellValueFactory(new PropertyValueFactory<>("court"));
        t2.setCellValueFactory(new PropertyValueFactory<>("duracion"));
        t3.setCellValueFactory(new PropertyValueFactory<>("horaIni"));
        t1.setEditable(false);t1.setSortable(false);
        t2.setEditable(false);t2.setSortable(false);
        t3.setEditable(false);t3.setSortable(false);
        t1.setId("columna"); t2.setId("columna"); t3.setId("columna");
        
        horarios.getColumns().addAll(t1,t2,t3);
        horarios.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        
        horarios.setItems(datos);
        Label titulo = new Label("Horarios reservados para "+actDate.format(DateTimeFormatter.ofPattern("dd-MM-yyyy"))+":");
        titulo.setFont(new Font(20));
        titulo.setId("titulo");
        
        ArrayList<Booking> reservas = clubPadelData.getCourtBookings
                (clubPadelData.getCourts().get(i).getName(),actDate);
        
        int duracionr = clubPadelData.getClubBookingDuration();
        
        String duracion;
        if(duracionr/60>1) duracion = duracionr/60+ " horas y "+duracionr%60+" minutos";
        else duracion = duracionr/60+ " hora y "+duracionr%60+" minutos";
        
        int m = 0;
        for(int j = 0; j < reservas.size() && m < this.clubPadelData.getClubBookingSlots(); j++){
            LocalTime h = reservas.get(j).getFromTime();
            String hora = h.toString().substring(0,5);
            
            String login=reservas.get(j).getMember().getLogin();
            
            m++;
            datos.add(new Pista(hora,duracion,login));
        }
        
        AnchorPane.setTopAnchor(titulo, 10.0);
        AnchorPane.setLeftAnchor(titulo, 60.0);
        AnchorPane.setTopAnchor(horarios, 40.0);
        AnchorPane.setLeftAnchor(horarios, 40.0);
        AnchorPane.setRightAnchor(horarios, 40.0);
        AnchorPane.setBottomAnchor(horarios, 40.0);
        anchorPane.getChildren().addAll(titulo,horarios);
        return anchorPane;
    }


    @FXML
    private void reservar(ActionEvent event) throws Exception{
        Stage bookingWindow = new Stage();
        FXMLLoader bookingl = new FXMLLoader(getClass().getResource("/vista_auxiliar/VistaFormularioReservar.fxml"));
        Parent root = bookingl.load();
        VistaFormularioReservar bookingController = bookingl.<VistaFormularioReservar>getController();
        bookingController.setDataBaseNMember(this.clubPadelData,this.member);
        bookingController.setDate(actDate);
        bookingWindow.setScene(new Scene(root));
        bookingWindow.setTitle("Reservar pista para día: "+actDate.format(DateTimeFormatter.ofPattern("dd-MM-yyyy")));
        bookingWindow.getIcons().add(new Image("/imagenes/icon.png"));
        bookingWindow.initModality(Modality.APPLICATION_MODAL);
        bookingWindow.setMinWidth(485);
        bookingWindow.setMinHeight(365);
        
        bookingWindow.showAndWait();
        eraseTabs();
        updatePistas();
    }
    
    private void eraseTabs(){
        while(!this.tabPane.getTabs().isEmpty())
            this.tabPane.getTabs().remove(0);
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
    
    public boolean courtIsReservedByUser(LocalTime ls){
        LocalTime lt = ls;
        ArrayList<Booking> ab = clubPadelData.getForDayBookings(actDate);
        for(int i = 0; i < ab.size(); i++){
            if(ab.get(i).getMember().equals(this.member)){
                if(ab.get(i).getFromTime().equals(lt)){return true;}
            }
        }
        return false;
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
