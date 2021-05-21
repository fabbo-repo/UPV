/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controlador;

import DBAcess.ClubDBAccess;
import java.net.URL;
import java.time.LocalDate;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.collections.ObservableList;
import javafx.collections.FXCollections;
import java.util.ArrayList;
import model.Booking;
import java.time.LocalTime;
import javafx.scene.control.TabPane;
import javafx.scene.control.Tab;
import javafx.scene.layout.AnchorPane;
import javafx.scene.control.Label;
import javafx.scene.text.Font;
import javafx.scene.control.TableView;
import extras.Pista;
import java.time.format.DateTimeFormatter;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TextArea;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;

/**
 * FXML Controller class
 *
 * @author Fabianno
 */
public class VistaPistasController implements Initializable {

    private ClubDBAccess clubPadelData;
    
    private LocalDate actDate;
    @FXML
    private TabPane tabPane;
    @FXML
    private TextArea infpanel;
    @FXML
    private ImageView inf;
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        actDate=LocalDate.now();
        this.tabPane.setId("tabPane");
    }    
    
    public void setDataBase(ClubDBAccess club) throws Exception{
        this.clubPadelData=club;
    }
    
    public void updatePistas() throws Exception{
        eraseTabs();
        for(int i = 0; i < clubPadelData.getCourts().size(); i++){
            
            this.tabPane.getTabs().add(
                    new Tab(clubPadelData.getCourts().get(i).getName(),createHorario(i)));
            
        }
    }
    
    private void eraseTabs(){
        while(!this.tabPane.getTabs().isEmpty())
            this.tabPane.getTabs().remove(0);
    }
    
    public AnchorPane createHorario(int i){
        AnchorPane anchorPane = new AnchorPane();
        anchorPane.setMaxSize(Double.MAX_VALUE,Double.MAX_VALUE);
        
        ArrayList<Pista> misdatos = new ArrayList<>();
        
	ObservableList datos = FXCollections.observableArrayList(misdatos);
	
        TableView<Pista> horarios = new TableView<>();
        horarios.setPrefSize(TableView.USE_COMPUTED_SIZE, TableView.USE_COMPUTED_SIZE);
        horarios.setPlaceholder(new Label("No hay reservas para esta pista hoy"));
        
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
        String fecha = LocalDate.now().toString();
        Label titulo = new Label("Horarios reservados para hoy ("+LocalDate.now().format(DateTimeFormatter.ofPattern("dd-MM-yyyy"))+"):");
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
    private void mouseOutInf(MouseEvent event) {
        infpanel.setVisible(false);
    }

    @FXML
    private void mouseOverInf(MouseEvent event) {
        infpanel.setVisible(true);
    }
    
}
