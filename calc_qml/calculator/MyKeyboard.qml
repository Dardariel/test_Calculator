import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Rectangle
{
    width: 250
    height: 190

    Grid
    {
        columns:  5
        rows: 4
        spacing: 10

        MyButton
        {
            id: mybutton7
            text: "7"
        }

        MyButton
        {
            id: mybutton8
            text: "8"
        }

        MyButton
        {
            id: mybutton9
            text: "9"
        }

        MyButton
        {
            id: mybuttonDivide
            text: "/"
        }
        Button
        {
            id: mybuttonC
            text: "C"
            width: 40
            height: 40
            onClicked: {lineEdit.text=""}
        }
        MyButton
        {
            id: mybutton4
            text: "4"
        }
        MyButton
        {
            id: mybutton5
            text: "5"
        }
        MyButton
        {
            id: mybutton6
            text: "6"
        }
        MyButton
        {
            id: mybuttonMultiply
            text: "*"
        }
        Button
        {
            id: mybuttonBackspace
            text: "<-"
            width: 40
            height: 40
            //onClicked: {appCore.qmlBackspace()}
        }
        MyButton
        {
            id: mybutton1
            text: "1"
        }
        MyButton
        {
            id: mybutton2
            text: "2"
        }
        MyButton
        {
            id: mybutton3
            text: "3"
        }
        MyButton
        {
            id: mybuttonMinus
            text: "-"
        }
        Rectangle
        {
            width: 40
            height: 40
        }
        MyButton
        {
            id: mybutton0
            text: "0"
        }
        MyButton
        {
            id: mybuttonDot
            text: "."
        }
        Rectangle
        {
            width: 40
            height: 40
        }
        MyButton
        {
            id: mybuttonPlus
            text: "+"
        }
        Button
        {
            id: mybuttonRes
            text: "="
            width: 40
            height: 40
            onClicked: {appCore.qmlResult(lineEdit.text)}
        }
    }
}

