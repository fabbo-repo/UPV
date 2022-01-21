/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controlador_auxiliar;

import model.Member;
import DBAcess.ClubDBAccess;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.TilePane;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

/**
 * FXML Controller class
 *
 * @author Yuuri
 * @author Fabianno
 */
public class VistaLoginController implements Initializable {
    private boolean cancelled;
    
    private Stage myStage;
    @FXML
    private TextField userText;
    @FXML
    private PasswordField passText;
    @FXML
    private CheckBox passSeeBox;
    @FXML
    private TextField umaskPass;
    
    private ClubDBAccess clubPadelData;
    @FXML
    private Label passState;
    @FXML
    private Label userState;
    
    private Member user;
    @FXML
    private GridPane panel;
    @FXML
    private TilePane pane;
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        this.cancelled = true;
        userText.textProperty().addListener(
            (observable,oldvalue,newvalue) ->
                {
                    //Con esto nos asuguramos de que no se habiliten los espacios
                    if(!newvalue.contains(" "))userText.setText(newvalue);
                    else userText.setText(oldvalue);
                }
            );
    }
    
    public void setDataBase(ClubDBAccess club){clubPadelData = club;}
    
    public boolean getCancelled(){return this.cancelled;}
    
    public Member getMember(){return this.user;}
    
    public void initStage(Stage x){
        this.myStage = x;
        this.myStage.setOnCloseRequest((WindowEvent event) ->{
            cancelled(null);
        });
        
    }

    @FXML
    private void buttonReleased(MouseEvent event) {
        Node button = (Node) event.getSource();
        button.setOpacity(button.getOpacity()+0.3);
    }

    @FXML
    private void buttonPressed(MouseEvent event) {
        Node button = (Node) event.getSource();
        button.setOpacity(button.getOpacity()-0.3);
    }

    @FXML
    private void showPass(ActionEvent event) {
        if(passSeeBox.isSelected()){
            umaskPass.setText(passText.getText());
            passText.setVisible(false);
            umaskPass.setVisible(true);
        }
        else{ 
            passText.setText(umaskPass.getText());
            umaskPass.setVisible(false);
            passText.setVisible(true);
        }
    }

    @FXML
    private void accepted(ActionEvent event) {
        if(clubPadelData.existsLogin(userText.getText())){
            if(passSeeBox.isSelected()){passText.setText(umaskPass.getText());}
            if(clubPadelData.getMemberByCredentials(userText.getText(),passText.getText())!=null){
                this.user = clubPadelData.getMemberByCredentials(userText.getText(),passText.getText());
                this.cancelled = false;
                this.myStage.hide();
                userText.setText("");
                passText.setText("");
                umaskPass.setVisible(false);
                passSeeBox.setSelected(false);
                passText.setVisible(true);
                userState.setText("");
                passState.setText("");
            }
            else{userState.setText("Usuario no registrado");passState.setText("");}
        }
        else{userState.setText("Usuario no registrado");passState.setText("");}
    }

    @FXML
    private void cancelled(ActionEvent event) {
        this.cancelled=true;
        this.myStage.hide();
        userText.setText("");
        passText.setText("");
        umaskPass.setVisible(false);
        passSeeBox.setSelected(false);
        passText.setVisible(true);
        userState.setText("");
        passState.setText("");
    }
}
