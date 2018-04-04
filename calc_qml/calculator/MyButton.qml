import QtQuick 2.0
import QtQuick.Controls 1.4

Button
{
    width: 40
    height: 40
    onClicked: { lineEdit.insert(lineEdit.length , text) }
}
