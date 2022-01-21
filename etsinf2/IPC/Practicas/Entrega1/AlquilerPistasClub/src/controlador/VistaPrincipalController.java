/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controlador;

import controlador_auxiliar.VistaRegisterController;
import controlador_auxiliar.VistaLoginController;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.Initializable;
import javafx.fxml.FXML;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;
import javafx.scene.control.TextArea;
import DBAcess.ClubDBAccess;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.layout.Pane;
import javafx.scene.text.Font;
import model.Member;

/**
 * FXML Controller class
 *
 * @author Yuuri
 * @author Fabianno
 */

public class VistaPrincipalController implements Initializable {

    private Stage miVentana;
    
    private ClubDBAccess clubPadelData;
    
    //Objetos controladores derivados de este
    private VistaRegisterController controladorRegister;
    private VistaLoginController controladorLogin;
    private VistaMenuController controladorMenu;
    private VistaPistasController controladorPistasD;
    
    //Objetos ventanas derivados de este
    private Stage ventanaRegister;
    private Stage ventanaLogin;
    private Stage ventanaPistasD;
    
    //Objetos escenas que se mostraran en miVentana
    private Stage ventanaMenu;
    
    @FXML
    private Pane pane0;
    @FXML
    private Pane pane1;
    @FXML
    private Button boton3;
    @FXML
    private Button boton2;
    @FXML
    private Button boton1;
    
    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {}    
    
    public void setControllers(VistaRegisterController vR, VistaLoginController vL, VistaPistasController vP, VistaMenuController vM){
        controladorRegister = vR;
        controladorLogin = vL;
        controladorPistasD = vP;
        controladorMenu = vM;
    }
    
    public void setWindows(Stage mP, Stage vR, Stage vL, Stage vP, Stage vM){
        miVentana = mP;
        ventanaRegister = vR;
        ventanaLogin = vL;
        ventanaPistasD = vP;
        ventanaMenu = vM;
        miVentana.maximizedProperty().addListener((observable)->{
            if(miVentana.isMaximized()){
                boton1.setFont(new Font(boton1.getFont().getName(),boton1.getFont().getSize()+14.0));
                boton2.setFont(new Font(boton2.getFont().getName(),boton2.getFont().getSize()+14.0));
                boton3.setFont(new Font(boton3.getFont().getName(),boton3.getFont().getSize()+14.0));
            }
            else{
                boton1.setFont(new Font(boton1.getFont().getName(),boton1.getFont().getSize()-14.0));
                boton2.setFont(new Font(boton2.getFont().getName(),boton2.getFont().getSize()-14.0));
                boton3.setFont(new Font(boton3.getFont().getName(),boton3.getFont().getSize()-14.0));
            }
        });
        
    }

    public void setDataBase(ClubDBAccess club){this.clubPadelData=club;}
    
    @FXML
    private void loginHandler(MouseEvent event) throws Exception{
        ventanaLogin.setMaximized(false);
        ventanaLogin.showAndWait();
        Member usuario = controladorLogin.getMember();
            
        if(!controladorLogin.getCancelled() && usuario!=null){
            controladorMenu.setMember(usuario);

            //Este codigo tiene la función de cambiar el escenario y encargarse
            //de que el tamaño de la ventana no se vea afectado con el cambio
            //de escenario
            changeScene();
        }
    }

    @FXML
    private void registerHandler(MouseEvent event) throws Exception{
        ventanaRegister.setMaximized(false);
        ventanaRegister.showAndWait();
        
        if(!controladorRegister.getCancelled()){
            saveData();
            
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Registro completado");
            alert.setHeaderText("Has sido registrado exitosamente");
            alert.setContentText("Proceda a autenticarse para reservar pistas");
            alert.show();
        }
    }
    
    @FXML
    private void pistasHandler(MouseEvent event) throws Exception{
        controladorPistasD.updatePistas();
        ventanaPistasD.setMaximized(false);
        ventanaPistasD.showAndWait();
    }

    
    private void changeScene(){
        boolean full = miVentana.isFullScreen();
        boolean max = miVentana.isMaximized();
        double h = miVentana.getHeight();
        double w = miVentana.getWidth();
        miVentana.hide();
        if(full){ventanaMenu.setFullScreen(true);}
        else if(max){ventanaMenu.setMaximized(true);}
        else{
            ventanaMenu.setHeight(h);
            ventanaMenu.setWidth(w);
        }
        ventanaMenu.show();
    }
    
    public void saveData(){
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle(clubPadelData.getClubName());
        alert.setHeaderText("Guradando los datos en DB");
        alert.setContentText("La aplicación está guardando los datos en la base de datos. Esto puede tardar algunos minutos.");
        alert.show();
        clubPadelData.saveDB();
        alert.hide();
    }

}
