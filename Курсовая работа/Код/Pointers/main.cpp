#include "mainwindow.hpp"

#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();

//}
int sizeOfSquare = 5;
struct Vertex{
    int x;
    int y;
    int value;
    Vertex(int xx, int yy, int vv): x(xx), y(yy), value(vv){};
    int sequence = new [] Vertex();
}
// MARK: WayGenerationStructure
// клас генерування шляху між усіма вершинами
class WayGen {
var vertexes = [[Vertex]]() // масив усіх вершин
var vertexSequence = [Vertex]() // згенерована послідовність(спочатку порожня) init(){
        // створюємо порожню матрицю 5x5
        vertexes = Array(repeating: Array(repeating: Vertex(), count: sizeOfSquare), count:
sizeOfSquare)
        for i in 0..<vertexes.count {
            for j in 0..<vertexes.count {
// присвоюємо координати X та Y клітинкам відповідно до їх розташування
                vertexes[i][j].x = i; vertexes[i][j].y = j
                // знаходимо для кожної клітинки доступні(по діагоналям, горизонталям та
вертикалям) клітинки
                vertexes[i][j].findEnabledCells(rowIndex: i, colIndex: j, array: vertexes)
            }
} }
}
extension Vertex{
// конструктор(за замовчуванням 0 по всім значенням) init(x: Int = 0, y: Int = 0, value: Int = 0) {
        self.x = x; self.y = y;
        self.value = value
    }
    // знаходження доступних клітинок(по діагоналям, горизонталям та вертикалям) для заданої
клітинки
    mutating func findEnabledCells(rowIndex: Int, colIndex: Int, array: [[Vertex]]) {
        // ітеруємося по матриці
        for i in 0..<array.count {
for j in 0..<array.count {
// доступні по горизонталям/вертикалям(лише один з індексів співпадає та
клітинка не є [0;0])
                if (i == rowIndex || j == colIndex) && !(i == rowIndex && j == colIndex) &&
!(i == 0 && j==0) {
                    let vert = Vertex(x: i, y: j, value: 0)
                    sequence.append(vert)
                    continue
}
                // доступні по діагоналям(дорівнюють суми індексів або суми відповідних
індексів)
5
                if ((rowIndex - i) == (colIndex - j) || (i + j) == (rowIndex + colIndex)) &&
!(i == rowIndex && j == colIndex) && !(i == 0 && j==0) {
                    let vert = Vertex(x: i, y: j, value: 0)
                    sequence.append(vert)
                    continue
} }
// MARK: WayGenerationClass Methods
extension WayGen{
    // генерація повного шляху та запис правильної послідовності у масив
     func findFullWay() -> [Vertex] {
        // за замовчуванням додаємо до правильного шляху вершину [0;0] у початок
        vertexSequence.append(vertexes[0][0])
        findWay(vertexes: vertexes) // викликаємо метод рекурсивного пошуку шляху
        return vertexSequence
} }
// MARK: WayGenerationClass Private Methods
private extension WayGen{
    // рекурсивна ф-ція генерації шляху
func findWay(vertexes: [[Vertex]]) -> Bool {
if vertexSequence.count == sizeOfSquare*sizeOfSquare {
return true // якщо розмір шляху дорівнює 25 -> базовий випадок -> вихід }
        // масив незайнятих вершин
var tempArray = Array(repeating: true, count: vertexSequence[vertexSequence.count- 1].sequence.count)
        // масив включених вершин
        let tempFalseArray = Array(repeating: false, count:
vertexSequence[vertexSequence.count-1].sequence.count)
// перебираємо масив доступних вершин до заданої та ставимо false біля кожної, якщо вона вже відвідана або є кінцевою вершиною(при тому, що невідвідані вершини ще залишилися)
for i in 0..<vertexSequence[vertexSequence.count - 1].sequence.count {
if vertexIsInWay(vertex: vertexSequence[vertexSequence.count - 1].sequence[i],
vertexes: vertexSequence) || ((vertexSequence[vertexSequence.count - 1].sequence[i].x == sizeOfSquare-1 && vertexSequence[vertexSequence.count - 1].sequence[i].y == sizeOfSquare - 1) && vertexSequence.count != sizeOfSquare*sizeOfSquare-1) {
                tempArray[i] = false
            }
}
var arrayDigit = [Int]() // допоміжний масив для фіксування використаних вершин при генерації
        var unusedDigits = [Int]() // допоміжний масив для фіксування невикористаних вершин
при генерації
for i in 0...vertexSequence[vertexSequence.count-1].sequence.count-1 {
// спочатку серед невикористаних вершин будуть усі доступні з вибраної клітинки unusedDigits.append(i)
}
} }
}
6

// формуємо випадковий набір доступних вершин до заданої(задля рандомізації
генерування)
for _ in 0...vertexSequence[vertexSequence.count-1].sequence.count-1 {
let temp = Int.random(in: 0...unusedDigits.count-1) arrayDigit.append(unusedDigits[temp])
unusedDigits.remove(at: temp) // використані вершини видаляємо з масиву
невикористаних
        }
        var count = 0 // лічильник для доступу по перемішаному масиву з індексами доступних
вершин
vertexes)
// поки
while tempArray != tempFalseArray {
let randDigit = arrayDigit[count]
count += 1
// переходимо на доступну вершину по згенерованому індексу
var randVert = vertexSequence[vertexSequence.count - 1].sequence[randDigit] randVert.findEnabledCells(rowIndex: randVert.x, colIndex: randVert.y, array:
vertexSequence.append(randVert) // додаємо вершину до шляху if tempArray[randDigit] && findWay(vertexes: vertexes) {
return true // якщо вершина була доступна та з неї можливо перейти на іншу вершину -> продовжуємо шукати шлях
} else{
то видаляємо її
// якщо вершина вже була зайнята або з неї неможливо продовжити шлях далі,
vertexSequence.remove(at: vertexSequence.count - 1)
} }
tempArray[randDigit] = false // відмічаємо по індексу цієї вершини false }
}
return false // базовий випадок -> шлях перебудовується }
// чи включена вершина до шляху
func vertexIsInWay(vertex: Vertex, vertexes: [Vertex]) -> Bool {
    // перевіряємо перебором серед усіх вершин шляху
    for i in vertexes {
        if vertex.x == i.x && vertex.y == i.y {
            return true
} }
return false
import Foundation
