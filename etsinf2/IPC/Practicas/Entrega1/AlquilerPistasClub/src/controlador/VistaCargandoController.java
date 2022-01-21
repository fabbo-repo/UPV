/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controlador;

import DBAcess.ClubDBAccess;
import controlador_auxiliar.VistaLoginController;
import controlador_auxiliar.VistaRegisterController;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.net.URL;
import java.util.Optional;
import java.util.ResourceBundle;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.image.Image;
import javafx.stage.Modality;
import javafx.stage.Stage;

public class VistaCargandoController extends Thread implements Initializable {

    private double width;
    private double height;
    private Dimension window;
    
    private VistaPrincipalController mainController;
    private VistaRegisterController registerController;
    private VistaLoginController loginController;
    private VistaMenuController menuController;
    private VistaPistasController courtController;
    
    private ClubDBAccess club;
    
    private Stage loadingWindow;
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
    }    
    
    @Override
    public void run(){
        try{
            //Cargamos el tamaño de la pantalla
            this.window = Toolkit.getDefaultToolkit().getScreenSize();
            this.width = (2*window.width)/3.0;
            this.height = (2*window.height)/3.0;
            System.out.println("Ajustando ventana a pantalla de: " + window.width+"x"+window.height);
            //El tamaño del escenario por default será 2/3 el tamaño de la pantalla
            
            //----------------------------------------------------------------------
            //Mientras se crean las subsventanas para mejorar eficiencia durante ejecución
            this.club = ClubDBAccess.getSingletonClubDBAccess();
            
            Stage mainWindow = createVentanaPrincipal();
            Stage registerWindow = createVentanaRegister();
            Stage loginWindow = createVentanaLogin();
            Stage menuWindow = createVentanaMenu();
            Stage courtWindow = createVentanaPistas();
            
            this.registerController.initStage(registerWindow);//Esto lo hago para que la propia ventana se puede cerrar
            this.registerController.setDataBase(club);
            
            this.loginController.initStage(loginWindow);//Esto lo hago para que la propia ventana se puede cerrar
            this.loginController.setDataBase(club);
            
            this.courtController.setDataBase(club);
            
            this.menuController.setWindows(menuWindow, mainWindow);
            this.menuController.setDataBase(club);
            
            this.mainController.setControllers(registerController, loginController, courtController, menuController);
            this.mainController.setWindows(mainWindow, registerWindow, loginWindow, courtWindow, menuWindow);
            this.mainController.setDataBase(club);
            
            //----------------------------------------------------------------------
            //Una vez cargado todo se cierra la ventana de carga y comienza el programa,
            //abriendo la ventana principal
            this.loadingWindow.hide();
            mainWindow.show();
        }
        catch(Exception e){
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Error");
            alert.setContentText("Se ha detectado un problema al ejecutar el programa");
            alert.showAndWait();
        }
    }
    
    public void setLoadingWindow(Stage l){
        this.loadingWindow = l;
    }
    
    private Stage createVentanaPrincipal() throws Exception{
        Stage mainWindow = new Stage();
        FXMLLoader mymain = new FXMLLoader(getClass().getResource("/vista/VistaPrincipal.fxml"));
        Parent root = mymain.load();
        this.mainController = mymain.<VistaPrincipalController>getController();
        Scene mainScene = new Scene(root,this.width,this.height);
        mainWindow.setScene(mainScene);
        mainWindow.setTitle(this.club.getClubName());
        mainWindow.getIcons().add(new Image("/imagenes/icon.png"));
        mainWindow.setMinWidth(this.window.width/2.0);
        mainWindow.setMinHeight((4*this.window.height)/5.0);
        mainWindow.setMaximized(true);
        return mainWindow;
    }
    
    private Stage createVentanaLogin() throws Exception{
        FXMLLoader mylogin = new FXMLLoader(getClass().getResource("/vista_auxiliar/VistaLogin.fxml"));
        Parent root = mylogin.load();
        this.loginController = mylogin.<VistaLoginController>getController();
        Scene scene = new Scene(root,320.0,180.0);
        Stage loginWindow = new Stage();
        loginWindow.setScene(scene);
        loginWindow.setTitle("Autenticación");
        loginWindow.getIcons().add(new Image("/imagenes/icon.png"));
        loginWindow.initModality(Modality.APPLICATION_MODAL);
        loginWindow.setMinWidth(this.window.width/4.0);
        loginWindow.setMinHeight(this.window.height/3.4);
        return loginWindow;
    }
    
    private Stage createVentanaRegister() throws Exception{
        FXMLLoader myregister = new FXMLLoader(getClass().getResource("/vista_auxiliar/VistaRegister.fxml"));
        Parent root = myregister.load();
        this.registerController = myregister.<VistaRegisterController>getController();
        Scene scene = new Scene(root,427.0,720.0);
        Stage registerWindow = new Stage();
        registerWindow.setScene(scene);
        registerWindow.setTitle("Registro");
        registerWindow.getIcons().add(new Image("/imagenes/icon.png"));
        registerWindow.initModality(Modality.APPLICATION_MODAL);
        
        registerWindow.setMinWidth(this.window.width/3.0);
        registerWindow.setMinHeight((4*this.window.height)/5.0);
        return registerWindow;
    }
    
    private Stage createVentanaMenu() throws Exception{
        FXMLLoader mymenu = new FXMLLoader(getClass().getResource("/vista/VistaMenu.fxml"));
        Parent root = mymenu.load();
        this.menuController = mymenu.<VistaMenuController>getController();
        Scene scene = new Scene(root,this.width,this.height);
        Stage menuWindow = new Stage(){
            @Override
            public void hide(){
                Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
                alert.setTitle("Salir");
                alert.setHeaderText("Precediendo a cerrar el programa");
                alert.setContentText("¿Deseas salir?");
                Optional<ButtonType> result = alert.showAndWait();
                if (result.isPresent() && result.get() == ButtonType.OK){
                    super.hide();
                }
            }
            @Override
            public void close(){super.hide();}
        };
        menuWindow.setScene(scene);
        menuWindow.setTitle(this.club.getClubName());
        menuWindow.getIcons().add(new Image("/imagenes/icon.png"));
        menuWindow.setMinWidth(this.window.width/2.0);
        menuWindow.setMinHeight((4*this.window.height)/5.0);
        return menuWindow;
    }
    
    private Stage createVentanaPistas() throws Exception{
        FXMLLoader mycourt = new FXMLLoader(getClass().getResource("/vista/VistaPistas.fxml"));
        Parent root = mycourt.load();
        this.courtController = mycourt.<VistaPistasController>getController();
        Scene scene = new Scene(root,this.window.width/3.0,this.height);
        Stage courtWindow = new Stage();
        courtWindow.setScene(scene);
        courtWindow.setTitle("Disponibilidad Pistas");
        courtWindow.getIcons().add(new Image("/imagenes/icon.png"));
        courtWindow.initModality(Modality.APPLICATION_MODAL);
        courtWindow.setMinWidth(this.window.width/2.0);
        courtWindow.setMinHeight((4*this.window.height)/5.0);
        return courtWindow;
    }
}
