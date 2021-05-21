/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controlador;

import DBAcess.ClubDBAccess;
import java.io.File;
import java.io.FileInputStream;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.MenuButton;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.BorderPane;
import javafx.stage.FileChooser;
import model.Member;

/**
 * FXML Controller class
 *
 * @author Fabianno
 */
public class VistaPerfilController implements Initializable {

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
    @FXML
    private Label nameState;
    @FXML
    private Label lastNameState;
    @FXML
    private Label phoneState;
    @FXML
    private Button buttonImageOtra;
    @FXML
    private ImageView imagePrePerfil;
    
    private BorderPane plataform;

    private Button imageButton;
    
    private Image imageMember;
    
    private Member member;
    
    private boolean cancelled;
    
    private ClubDBAccess clubPadelData;
    
    
    private MenuButton perfilButton;
    @FXML
    private TextArea infpanel;
    
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        this.cancelled=true;
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
    
    public void setPlataforma(BorderPane p){
        this.plataform=p;
    }

    public void setMember(Member p){
        this.member=p;
        nameField.setText(this.member.getName());
        lastNameField.setText(this.member.getSurname());
        userField.setText(this.member.getLogin());
        passwordField.setText(this.member.getPassword());
        phoneField.setText(this.member.getTelephone());
        creditCardField.setText(this.member.getCreditCard());
        svcField.setText(this.member.getSvc());
        if(this.member.getImage()!=null) imagePrePerfil.setImage(this.member.getImage());
        else imagePrePerfil.setImage(new Image("/imagenes/defaultProfile.png"));
    }

    @FXML
    private void acceptHandler(ActionEvent event) {
        eraseAllState();
        if(allFine()){
            this.cancelled = false;
            saveMember();
            perfilButton.setText(this.member.getLogin());
            ((ImageView)perfilButton.getGraphic()).setImage(this.member.getImage());
            this.plataform.setCenter(null);
            this.eraseAll();
        }
        
    }
    
    public void setProfileMenu(MenuButton mb){
        perfilButton=mb;
    }

    @FXML
    private void cancelHandler(ActionEvent event) {
        this.plataform.setCenter(null);
        this.eraseAll();
    }
    
    public void setDataBase(ClubDBAccess club) throws Exception{
        this.clubPadelData=club;
    }
    
    @FXML
    private void buttonImageHandler(ActionEvent event) throws Exception{
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
            fileChooser.getExtensionFilters().addAll(new FileChooser.ExtensionFilter("Imágenes", "*.png", "*.jpg", "*.gif"));
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
        if(imageMember!=null)imagePrePerfil.setImage(imageMember);
        else imagePrePerfil.setImage(new Image("/imagenes/defaultProfile.png"));
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
        
        if(this.member.getLogin().equals(userField.getText())||!this.clubPadelData.existsLogin(userField.getText())){}
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
    
    public void saveMember(){
        this.member.setName(nameField.getText());
        this.member.setSurname(lastNameField.getText());
        this.member.setLogin(userField.getText());
        this.member.setPassword(passwordField.getText());
        this.member.setTelephone(phoneField.getText());
        this.member.setCreditCard(creditCardField.getText());
        this.member.setSvc(svcField.getText());
        if(imagePrePerfil!=null && imagePrePerfil.getImage()!=null)
            this.member.setImage(imagePrePerfil.getImage());
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