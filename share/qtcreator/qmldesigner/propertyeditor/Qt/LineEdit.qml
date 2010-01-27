import Qt 4.6
import Bauhaus 1.0

QWidget {
    id: LineEdit

    property var backendValue

    minimumHeight: 24;

    QLineEdit {
        id: lineEditWidget
        x: 18
        width: LineEdit.width - 18
        height: LineEdit.height

        text: backendValue.value

        onTextEdited: {
            print("text edited")
            backendValue.value = text
        }


    }    
    ExtendedFunctionButton {
        backendValue: LineEdit.backendValue
        y: 4
        x: 3
        visible: LineEdit.enabled
    }
}
