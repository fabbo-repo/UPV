/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controlador_auxiliar;

import DBAcess.ClubDBAccess;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.stage.FileChooser;
import javafx.stage.FileChooser.ExtensionFilter;
import java.io.File;
import javafx.scene.Node;
import javafx.scene.control.Alert;
import java.io.FileInputStream;
import javafx.scene.layout.TilePane;
import model.Member;

/**
 * FXML Controller class
 *
 * @author Fabianno
 */
public class VistaRegisterController implements Initializable {
    
    private boolean cancelled;
    private Stage myStage;
    @FXML
    private TextField nameField;
    @FXML
    private TextField lastNameField;
    @FXML
    private TextField phoneField;
    @FXML
    private TextField userField;
    @FXML
    private TextField passwordField;
    @FXML
    private TextField creditCardField;
    @FXML
    private TextField svcField;
    @FXML
    private Label userState;
    @FXML
    private Label passState;
    @FXML
    private Label creditCardState;
    
    private ClubDBAccess clubPadelData;
    @FXML
    private Label lastNameState;
    @FXML
    private Label phoneState;
    @FXML
    private Label nameState;
    @FXML
    private Button buttonImageOtra;
    
    private Button imageButton;
    
    private Image imageMember;
    @FXML
    private TilePane pane;
    
    public void initStage(Stage x){
        this.myStage = x;
        this.myStage.setOnCloseRequest((WindowEvent event) ->{
            cancelHandler(null);
        });
        phoneField.textProperty().addListener(
            (observable,oldvalue,newvalue) ->
                {
                    if(newvalue.matches("[0-9]*"))phoneField.setText(newvalue);
                    else phoneField.setText(oldvalue);
                }
            );
        creditCardField.textProperty().addListener(
            (observable,oldvalue,newvalue) ->
                {
                    if(newvalue.matches("[0-9]*")&&newvalue.length()<=16)creditCardField.setText(newvalue);
                    else creditCardField.setText(oldvalue);
                }
            );
        svcField.textProperty().addListener(
            (observable,oldvalue,newvalue) ->
                {
                    if(newvalue.matches("[0-9]*")&&newvalue.length()<=3)svcField.setText(newvalue);
                    else svcField.setText(oldvalue);
                }
            );
        userField.textProperty().addListener(
            (observable,oldvalue,newvalue) ->
                {
                    //Con esto nos asuguramos de que no se habiliten los espacios
                    if(!newvalue.contains(" "))userField.setText(newvalue);
                    else userField.setText(oldvalue);
                }
            );
        passwordField.textProperty().addListener(
            (observable,oldvalue,newvalue) ->
                {
                    if(newvalue.matches("[0-9, A-z]*"))passwordField.setText(newvalue);
                    else passwordField.setText(oldvalue);
                }
            );
    }

    public void setDataBase(ClubDBAccess club){clubPadelData = club;}
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        this.cancelled = true;
    }    
    
    public boolean getCancelled(){return this.cancelled;}

    @FXML
    private void acceptHandler(ActionEvent event) {
        eraseAllState();
        if(allFine()){
            this.cancelled=false;
            this.clubPadelData.getMembers().add(
                    new Member(nameField.getText(),lastNameField.getText(),phoneField.getText(),
                            userField.getText(),passwordField.getText(),
                            creditCardField.getText(),svcField.getText(),imageMember));
            
            this.myStage.hide();
            eraseAll();
        }
    }

    @FXML
    private void cancelHandler(ActionEvent event) {
        this.cancelled=true;
        this.myStage.hide();
        eraseAll();
    }
    
    public void eraseAll(){
        nameField.setText("");
        lastNameField.setText("");
        userField.setText("");
        passwordField.setText("");
        phoneField.setText("");
        creditCardField.setText("");
        userState.setText("");
        passState.setText("");
        creditCardState.setText("");
        nameState.setText("");
        lastNameState.setText("");
        phoneState.setText("");
        svcField.setText("");
        if(this.imageButton!=null)this.imageButton.setOpacity(this.imageButton.getOpacity()+0.6);
        imageMember=null;
        imageButton=null;
    }
    
    public void eraseAllState(){
        userState.setText("");
        passState.setText("");
        creditCardState.setText("");
        nameState.setText("");
        lastNameState.setText("");
        phoneState.setText("");
    }
    public boolean allFine(){
        boolean flag = true;
        if(nameField.getText().length()==0){flag=false;this.nameState.setText("Campo nombre obligatorio");}
        if(lastNameField.getText().length()==0){flag=false;this.lastNameState.setText("Campo apellidos obligatorio");}
        if(phoneField.getText().length()==0){flag=false;this.phoneState.setText("Campo teléfono obligatorio");}
        if(userField.getText().length()==0){flag=false;this.userState.setText("Campo mombre de usuario obligatorio");}
        
        if(!this.clubPadelData.existsLogin(userField.getText())){}
        else{
            flag=false;
            this.userState.setText("Ya existe un usuario con este nombre de usuario");
        }
        if(passwordField.getText().length()>6){}
        else{
            flag=false;
            this.passState.setText("Contraseña debe tener más de 6 caracteres");
        }
        if(creditCardField.getText().length()>0){
            if(creditCardField.getText().length()==16){
                if(svcField.getText().length()>0){
                    if(svcField.getText().length()==3){}
                    else{
                        flag=false;
                        this.creditCardState.setText("Número de código de seguridad debe tener 3 números");
                    }
                }
            }
            else{
                flag=false;
                this.creditCardState.setText("Número de tarjeta de crédito debe tener 16 números");
            }
        }
        return flag;
    }

    @FXML
    private void buttonImageHandler(ActionEvent event) {
        if(this.imageButton!=null)this.imageButton.setOpacity(this.imageButton.getOpacity()+0.6);
        if(((Button) event.getSource())!= this.buttonImageOtra){
            this.imageButton = ((Button) event.getSource());
            this.imageButton.setOpacity(this.imageButton.getOpacity()-0.6);
            this.imageMember = ((ImageView) this.imageButton.getGraphic()).getImage();
        }
        else{
            this.imageButton=null;
            //Ahora se debe abrir una ventana para seleccionar una imagen tipo png
            FileChooser fileChooser = new FileChooser();
            fileChooser.setTitle("Abrir imagen");
            fileChooser.getExtensionFilters().addAll(new ExtensionFilter("Imágenes", "*.png", "*.jpg", "*.gif"));
            File selectedFile = fileChooser.showOpenDialog(((Node)event.getSource()).getScene().getWindow());
            if (selectedFile != null) {
                try{
                    this.imageMember = new Image(new FileInputStream(selectedFile.getPath()));
                }
                catch(Exception e){
                    Alert alert = new Alert(Alert.AlertType.ERROR);
                    alert.setTitle("Error");
                    alert.setHeaderText("Error");
                    alert.setContentText("Se ha detectado un problema al cargar la imagen");
                    alert.showAndWait();
                }
            }
            else{imageMember=null;}
        }
    }
}
