/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controlador;

import DBAcess.ClubDBAccess;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;
import java.util.Optional;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuButton;
import model.Member;
import javafx.scene.image.ImageView;
import javafx.stage.WindowEvent;

/**
 * FXML Controller class
 *
 * @author Fabianno
 */
public class VistaMenuController implements Initializable {

    @FXML
    private BorderPane panel;
    
    private Stage myStage;
    
    private Stage mainWindow;
    
    private ClubDBAccess clubPadelData;
    
    private Member user;
    @FXML
    private MenuButton perfilButton;
    @FXML
    private ImageView barImage;
    
    @FXML
    private Menu reservarPistas;
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {}    
    
    public void setWindows(Stage mP, Stage sP){
        this.myStage=mP;
        mainWindow=sP;
        this.myStage.setOnCloseRequest((WindowEvent event) ->{
            saveData();
        });
    }
    
    public void setDataBase(ClubDBAccess club) throws Exception{
        this.clubPadelData=club;
        
    }
    
    public void setMember(Member us){
        this.user = us;
        String nickname = this.user.getLogin();
        this.perfilButton.setText(nickname);
        if(this.user.getImage()!=null){
            try{
                barImage.imageProperty().setValue(this.user.getImage());
            }
            catch(Exception e){
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error");
                alert.setHeaderText("Error");
                alert.setContentText("Se ha detectado un problema al cargar la imagen");
                alert.showAndWait();
            }
        }
    }
    
    @FXML
    private void cerrarSesion(ActionEvent event) throws Exception {
        Alert alert = new Alert(AlertType.CONFIRMATION);
        alert.setTitle("Cerrar Sesión");
        alert.setHeaderText("Precediendo a cerrar sesión");
        alert.setContentText("¿Deseas cerrar sesión en: "+ this.user.getLogin()+"?");
        Optional<ButtonType> result = alert.showAndWait();
        
        if (result.isPresent() && result.get() == ButtonType.OK){
            saveData();
            //Este codigo tiene la función de cambiar el escenario y encargarse
            //de que el tamaño de la ventana no se vea afectado con el cambio
            //de escenario
            changeScene();
        } 
    }

    @FXML
    private void exitApp(ActionEvent event) throws Exception{
        saveData();
        myStage.hide();
    }
    
    private void changeScene(){
        boolean full = myStage.isFullScreen();
        boolean max = myStage.isMaximized();
        double h = myStage.getHeight();
        double w = myStage.getWidth();
        myStage.close();
        this.panel.setCenter(null);
        if(full){mainWindow.setFullScreen(true);}
        else if(max){mainWindow.setMaximized(true);}
        else{
            mainWindow.setHeight(h);
            mainWindow.setWidth(w);
        }
        mainWindow.show();
    }
    
    public void saveData(){
        Alert alert = new Alert(AlertType.INFORMATION);
        alert.setTitle(clubPadelData.getClubName());
        alert.setHeaderText("Guardando los datos en DB");
        alert.setContentText("La aplicación está guardando los datos en la base de datos. Esto puede tardar algunos minutos.");
        alert.show();
        clubPadelData.saveDB();
        alert.hide();
    }
    
    
    public void invokeError(){
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Error");
        alert.setHeaderText("Error");
        alert.setContentText("Se ha detectado un problema al ejecutar el programa");
        alert.showAndWait();
    }


    @FXML
    private void verPerfil(ActionEvent event) throws Exception{
        FXMLLoader miPerfil = new FXMLLoader(getClass().getResource("/vista/VistaPerfil.fxml"));
        Parent root = miPerfil.load();
        VistaPerfilController perfil = miPerfil.<VistaPerfilController>getController();
        perfil.setPlataforma(panel);
        perfil.setMember(this.user);
        perfil.setDataBase(clubPadelData);
        perfil.setProfileMenu(this.perfilButton);
        this.panel.setCenter(root);
        
    }

    @FXML
    private void verMisReservas(ActionEvent event) throws Exception{
        FXMLLoader misReservas = new FXMLLoader(getClass().getResource("/vista/VistaReservas.fxml"));
        Parent root = misReservas.load();
        VistaReservasController reserva = misReservas.<VistaReservasController>getController();
        reserva.setDataBaseNMember(clubPadelData,this.user);
        this.panel.setCenter(root);
    }

    @FXML
    private void reservarPista(ActionEvent event) throws Exception{
        FXMLLoader misReservar = new FXMLLoader(getClass().getResource("/vista/VistaReservar.fxml"));
        Parent root = misReservar.load();
        VistaReservarController reserva = misReservar.<VistaReservarController>getController();
        reserva.setDataBaseNMember(clubPadelData,this.user);
        this.panel.setCenter(root);
    }
    
}
