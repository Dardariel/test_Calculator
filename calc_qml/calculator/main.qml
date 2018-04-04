import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

import MyValidator 1.0

Window
{
    id: mainWindow
    Connections
    {
        target: appCore
        onSendToQmlLog:
        {
            listModel.append({ textList: text, textColor: color })
        }
        onSendToQmlRes:
        {
            lblRes.text="Res: "+count
        }
        onSendToQmlReq:
        {
            lblReq.text="Res: "+count
        }
    }


    // настройка окна
    visible: true
    minimumHeight: 600
    minimumWidth: 600


    MyValidator
    {
        id:myValid

        onSignalLog:
        {
            listModel.append({ textList: text, textColor: color})
        }
    }

    Row
    {
        id: mainRow
        spacing: 5
        padding: 10


        ListView
        {
            id: listView

            width: mainWindow.width-(columnRightPanel.width+20)
            height: mainWindow.height-50

            delegate: Text
            {
                anchors.left: parent.left
                anchors.right: parent.right
                height: 20
                verticalAlignment: Text.AlignVCenter

                text: textList
                color: textColor
            }

            model: ListModel
            {
                id: listModel
            }

            onCountChanged: {
               listView.positionViewAtEnd()
            }

        }


        Column
        {
            id: columnRightPanel
            spacing: 5
            padding: 10


            TextField
            {
                property bool valid: false
                width: 250
                id: lineEdit
                objectName: 'lineEdit'
                textColor: acceptableInput ? "black" : "red"
                validator: myValid
            }

            MyKeyboard
            {
                id: myKeyboard
            }

            Rectangle
            {
                width: 250
                height: mainWindow.height-(lineEdit.height+myKeyboard.height+queueLay.height+50)

            }

            Row
            {
                id: queueLay
                spacing: 5

                Column
                {
                    spacing: 5
                    Label
                    {
                        id: lblReq
                        objectName: "lblReq"
                        text: "Req: 0"
                    }

                    SpinBox
                    {
                        id: spinboxReq
                        objectName: "spinReq"
                        maximumValue: 100000
                        minimumValue: 1
                        value: 1000
                        suffix: " ms"

                        onValueChanged: {appCore.qmlTimerChangeReq(value)}

                    }
                } //collumn Req
                Column
                {
                    spacing: 5
                    Label
                    {
                        id: lblRes
                        objectName: "lblRes"
                        text: "Res: 0"
                    }

                    SpinBox
                    {
                        id: spinboxRes
                        objectName: "spinRes"
                        maximumValue: 100000
                        minimumValue: 1
                        value: 100
                        suffix: " ms"

                        onValueChanged: {appCore.qmlTimerChangeRes(value)}

                    }
                } //column Res
            } // row queue
        } // column right panel
    } // row all object
}



