class TNode{
    data: number;
    next: any;
    constructor(data:number) {
        this.data = data;
        this.next = null;
    }
}

class LinkedList{
    head: TNode;
    length: number = 0;

    constructor(data: number) {
        this.head = new TNode(data);
        this.length++;
    }

    insertEnd(data: number): void{
        let cur = this.head;
        
        while(cur != null) {
            if(cur.next == null) break;
            cur = cur.next;
        }

        const newNode = new TNode(data);
        cur.next = newNode;
        this.length++;
    }

    insertBegin(data: number): void{
        const newNode = new TNode(data);
        newNode.next = this.head;
        this.head = newNode;
        this.length++;
    }

    printLinkedList(): number{
        let cur = this.head;
        while(cur != null) {
            console.log(cur.data);
            cur = cur.next;
        }
        return this.length;
    }

    sortSelection(type: boolean): void{
        const f = type ? (A: TNode, B: TNode):number => B.data - A.data : (A: TNode, B: TNode):number => A.data - B.data;
        let cur = this.head;
        while(cur.next != null) {
            let nextCur = cur.next;
            let min = cur;
            while(nextCur != null) {
                if(f(min, nextCur) > 0) min = nextCur;
                nextCur = nextCur.next;
            }
            //swap(cur, min);
            cur = cur.next;
        }
    }
}

class Pilha {
    topo: TNode|null;
    base: TNode|null;

    constructor() {
        this.topo = null;
        this.base = null;
    }

    queue(data: number): void {
        const newNode = new TNode(data);
        if(this.base == null) this.base = newNode;
        if(this.topo != null) this.topo.next = newNode;
        this.topo = newNode;
    }

    dequeue(): number{
        let numeroRemovido: number;
        numeroRemovido = (this.topo != null) ? this.topo.data : -666;

        if(this.base == this.topo){
            this.topo = null;
            this.base = null;
        }
        else{
            let cur = this.base;
            while(cur != null && cur.next != this.topo){
                cur = cur.next;
            }
            this.topo = cur;
        }
        return numeroRemovido;
    }
}

function getPrev(head: TNode, node: TNode): TNode{
    let cur:TNode = head;
    while(head.next != node && head != null) {
        head = head.next;
    }
    
    return cur;
}

//let ll = new LinkedList("A")
