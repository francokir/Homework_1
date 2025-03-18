/*Para este ejercicio me parecio conveniente utilizar un struct para los nodos, almacenando estos un valor
y al ser enlazada la lista, un puntero al siguiente (usando unique). El trabajo pedia 6 funciones. 
La primera, create node, la mas corta y lo que hace simplemente es crear el nodo (el usuario le debe pasar
 el valor que almacene este), y lo creacon el tipo nodo que creamos el struct anteriormente, y usamos el make unique 
de esta forma no nos encargamos de liberar asignar ni nada (memoria). 
La segunda funcion inserta un nodo al principio de nuestra lista enlazada, reutilizamos claramente nuesrta funcion new node
para crear el nodo, y uso auto por las dudas de que cambie el tipo (no estoy seguro de si es necesario pero
 note en las clases que es recomendable). Como en el struct contemplamos el puntero al siguiente, aprovechamos ese
 struct y asignamos con el move, el puntero actual de la lista del primer nodo a new node next y head toma 
 posesion de new node luego. (el siguiente del nuevo nodo era el anterior head, y luego se pone como nuevo head
 el nuevo nodo)
 el push back lo que hace es insertar atras de todo, para ello, creo el nodo, verifico que la lista no este vacia (
 de serlo inserto como el head el nuevo nodo) , luego de esa condicion recorro los nodos hasta encontrar el ultimo
 y hago que el siguiente de ese ultimo.
 El insert, al principio aprovecho el push front en el caso de que me pidan insertar al principio (posicion 0, agregue 
 menor por costumbre de tps de viejas materias, por si hay error y se pide inseertar en posicion negativa, nuevamente
 no me parecio necesario) . De no ser 0 la posicion, busco el  lugar donde insertar, como hago eso: con un while
 fijandome que exista el siguiente del nodo donde estoy recorriendo, y que sea una posicion anterior a la pedida, 
 me guardo el nodo y asigno que el siguiente del mismo sea el nodo creado nuevo y el siguiente del nuevo apunte al que
 anteriormente era el siguiente de temp.
 Para el erase, primero si la lista esta vacia no borro nada, otro caso si queremos eliminar el primero o si hay 
 un solo nodo, para esto hago que el head, sea el siguiente del mismo, si habia uno solo se elimina y apunta a 
 null ptr. Recorro la lista hasta encontrarme antes del nodo a eliminar, por eso chequeo que exista el siguiente, 
 y el siguiente del siguiente (contando el caso que queramos borrar al final) lo que hago es, frenarme en el nodo temp
 que seria el anterior a borrar, y hago que su siguiente sea el siguiente del siguiente (el del medio se borra)
 para printear la lista, chequeo de que exista head y no este vacia, luego con un while voy recorriendo y obteniendo
 todos los valores
 En el main jugue un poco y fui probando valores y probando prints intermedios

 */

#include <iostream>
#include <memory>

using namespace std;

struct Node {
    int value;
    unique_ptr<Node> next;
};

unique_ptr<Node> create_node(int value) {
    return make_unique<Node>(Node{value, nullptr});
}

void push_front(unique_ptr<Node>& head, int value) {
    auto new_node = create_node(value);
    new_node->next = move(head);
    head = move(new_node);
}

void push_back(unique_ptr<Node>& head, int value) {
    auto new_node = create_node(value);
    if (!head) {
        head = move(new_node);
        return;
    }
    Node* temp = head.get();
    while (temp->next) {
        temp = temp->next.get();
    }
    temp->next = move(new_node);
}

void insert(unique_ptr<Node>& head, int value, int pos) {
    if (pos <= 0) {
        push_front(head, value);
        return;
    }
    Node* temp = head.get();
    int index = 0;
    while (temp->next && index < pos - 1) {
        temp = temp->next.get();
        index++;
    }
    auto new_node = create_node(value);
    new_node->next = move(temp->next);
    temp->next = move(new_node);
}

void erase(unique_ptr<Node>& head, int pos) {
    if (!head) return;
    if (pos == 0 || !head->next) {
        head = move(head->next);
        return;
    }
    Node* temp = head.get();
    int index = 0;
    while (temp->next && temp->next->next && index < pos - 1) {
        temp = temp->next.get();
        index++;
    }
    temp->next = move(temp->next->next);
}

void print_list(const unique_ptr<Node>& head) {
    const Node* temp = head.get();
    while (temp) {
        cout << temp->value;
        if (temp->next) cout << " -> ";
        temp = temp->next.get();
    }
    cout << endl;
}

int main() {
    unique_ptr<Node> head = nullptr;

    push_back(head, 9);
    push_back(head, 73);
    push_back(head, 27);
    print_list(head);
    push_front(head, 100);
    print_list(head); 
    insert(head, 5, 101);
    print_list(head);  
    erase(head, 3);
    print_list(head);  
    erase(head, 10);
    print_list(head);  

    return 0;
}
