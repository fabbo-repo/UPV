package aplicacion;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import java.awt.Toolkit;
import java.awt.Dimension;
import javafx.scene.image.Image;
import controlador.VistaCargandoController;
import javafx.application.Platform;
import javafx.scene.control.Alert;
import javafx.stage.StageStyle;

/**
 * @author Lishuang Sun 
 * @author Fabián Scherle Carboneres
 */
public class Aplicacion extends Application {
    
    @Override
    public void start(Stage mainstage){
        try{
            Stage loadingWindow = createVentanaCargando();
            loadingWindow.show();
        }
        catch(Exception e){
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Error");
            alert.setContentText("Se ha detectado un problema al ejecutar el programa");
            alert.show();
        }
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
    
    private Stage createVentanaCargando() throws Exception{
        FXMLLoader mymain = new FXMLLoader(getClass().getResource("/vista/VistaCargando.fxml"));
        Parent root = mymain.load();
        VistaCargandoController lController = mymain.<VistaCargandoController>getController();
        Dimension window = Toolkit.getDefaultToolkit().getScreenSize();
        Stage loadingWindow = new Stage();
        Scene loadingScene = new Scene(root,(4*window.width)/5.0,(4*window.height)/5.0);
        loadingWindow.setScene(loadingScene);
        loadingWindow.setResizable(false);
        loadingWindow.getIcons().add(new Image("/imagenes/icon.png"));
        loadingWindow.initStyle( StageStyle.UNDECORATED );
        lController.setLoadingWindow(loadingWindow);
        Platform.runLater(lController);
        return loadingWindow;
    }
    
}