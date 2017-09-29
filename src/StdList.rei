let length: list 'a => int; /* Return the length (number of elements) of the given list. */

let head: list 'a => option 'a;
/** Return the first element of the given list. Returns None if the list is empty. */

let tail: list 'a => list 'a;
/* Return the given list without its first element. */

let nth: int => list 'a => option 'a;
/* Return the n-th element of the given list. The first element (head of the list) is at position 0. Returns None if the element does not exist */

let reverse: list 'a => list 'a;
/* List reversal. */

let append: list 'a => list 'a => list 'a;
/* Catenate two lists. Same function as the infix operator @. Not tail-recursive (length of the first argument). The @ operator is not tail-recursive either. */

let reverseAppend: list 'a => list 'a => list 'a;
/* List.rev_append l1 l2 reverses l1 and concatenates it to l2. This is equivalent to List.reverse l1 @ l2, but reverseAappend is tail-recursive and more efficient. */

let concat: list (list 'a) => list 'a;
/* Concatenate a list of lists. The elements of the argument are all concatenated together (in the same order) to give the result. Not tail-recursive (length of the argument + length of the longest sub-list). */

let flatten: list (list 'a) => list 'a;
/* Same as concat. Not tail-recursive (length of the argument + length of the longest sub-list). */


/* Iterators */


let iter: ('a => unit) => list 'a => unit;
/* List.iter f [a1; ...; an] applies function f in turn to a1; ...; an. It is equivalent to begin f a1; f a2; ...; f an; () end. */

let iteri: (int => 'a => unit) => list 'a => unit;
/* Same as List.iter, but the function is applied to the index of the element as first argument (counting from 0), and the element itself as second argument. */

let map: ('a => 'b) => list 'a => list 'b;
/* List.map f [a1; ...; an] applies function f to a1, ..., an, and builds the list [f a1; ...; f an] with the results returned by f. Not tail-recursive. */

let mapi: (int => 'a => 'b) => list 'a => list 'b;
/* Same as List.map, but the function is applied to the index of the element as first argument (counting from 0), and the element itself as second argument. Not tail-recursive. */

let reverseMap: ('a => 'b) => list 'a => list 'b;
/* List.reverseMap f l gives the same result as List.rev (List.map f l), but is tail-recursive and more efficient. */

let foldLeft: ('a => 'b => 'a) => 'a => list 'b => 'a;
/* List.foldLeft f a [b1; ...; bn] is f (... (f (f a b1) b2) ...) bn. */

let foldRight: ('a => 'b => 'b) => list 'a => 'b => 'b;
/* List.foldRight f [a1; ...; an] b is f a1 (f a2 (... (f an b) ...)). Not tail-recursive. */

/* Iterators on two lists */

let iter2: ('a => 'b => unit) => list 'a => list 'b => unit;
/* List.iter2 f [a1; ...; an] [b1; ...; bn] calls in turn f a1 b1; ...; f an bn. Ignores remaining elements if lists are not the same length. */

let map2: ('a => 'b => 'c) => list 'a => list 'b => list 'c;
/* List.map2 f [a1; ...; an] [b1; ...; bn] is [f a1 b1; ...; f an bn]. Ignores remaining elements if lists are not the same length */

let reverseMap2: ('a => 'b => 'c) => list 'a => list 'b => list 'c;
/* List.reverseMap2 f l1 l2 gives the same result as List.rev (List.map2 f l1 l2), but is tail-recursive and more efficient.  Ignores remaining elements if lists are not the same length*/

let foldLeft2: ('a => 'b => 'c => 'a) => 'a => list 'b => list 'c => 'a;
/* List.foldLeft2 f a [b1; ...; bn] [c1; ...; cn] is f (... (f (f a b1 c1) b2 c2) ...) bn cn.  Ignores remaining elements if lists are not the same length */

let foldRight2: ('a => 'b => 'c => 'c) => list 'a => list 'b => 'c => 'c;
/* List.foldRight2 f [a1; ...; an] [b1; ...; bn] c is f a1 b1 (f a2 b2 (... (f an bn c) ...)).  Ignores remaining elements if lists are not the same length. Not tail-recursive. */


/* List scanning */


let forAll: ('a => bool) => list 'a => bool;
/* forAll p [a1; ...; an] checks if all elements of the list satisfy the predicate p. That is, it returns (p a1) && (p a2) && ... && (p an). */

let exists: ('a => bool) => list 'a => bool;
/* exists p [a1; ...; an] checks if at least one element of the list satisfies the predicate p. That is, it returns (p a1) || (p a2) || ... || (p an). */

let forAll2: ('a => 'b => bool) => list 'a => list 'b => bool;
/* Same as List.forAll, but for a two-argument predicate.*/

let exists2: ('a => 'b => bool) => list 'a => list 'b => bool; 
/* Same as List.exists, but for a two-argument predicate.*/

let contains: 'a => list 'a => bool;
/* mem a l is true if and only if a is equal to an element of l. */


/* List searching */


let find: ('a => bool) => list 'a => option 'a;
/* find p l returns the first element of the list l that satisfies the predicate p.*/

let filter: ('a => bool) => list 'a => list 'a;
/* filter p l returns all the elements of the list l that satisfy the predicate p. The order of the elements in the input list is preserved. */


let partition: ('a => bool) => list 'a => (list 'a, list 'a);
/* partition p l returns a pair of lists (l1, l2), where l1 is the list of all the elements of l that satisfy the predicate p, and l2 is the list of all the elements of l that do not satisfy p. The order of the elements in the input list is preserved. */

/* Association lists */

let assoc: 'a => list ('a, 'b) => option 'b;
/* assoc a l returns the value associated with key a in the list of pairs l. That is, assoc a [ ...; (a,b); ...] = b if (a,b) is the leftmost binding of a in list l. */


let containsAssoc: 'a => list ('a, 'b) => bool;
/* Same as List.assoc, but simply return true if a binding exists, and false if no bindings exist for the given key. */


let removeAssoc: 'a => list ('a, 'b) => list ('a, 'b);
/* removeAssoc a l returns the list of pairs l without the first pair with key a, if any. Not tail-recursive. */



/* Lists of pairs */


let split: list ('a, 'b) => (list 'a, list 'b);
/* Transform a list of pairs into a pair of lists: split [(a1,b1); ...; (an,bn)] is ([a1; ...; an], [b1; ...; bn]). Not tail-recursive. */

let zip: list 'a => list 'b => list ('a, 'b); 
/* Transform a pair of lists into a list of pairs: zip [a1; ...; an] [b1; ...; bn] is [(a1,b1); ...; (an,bn)]. Ignores remaining elements if lists are not the same length. */


/* Sorting */


let sort: ('a => 'a => int) => list 'a => list 'a;
/* Sort a list in increasing order according to a comparison function. The comparison function must return 0 if its arguments compare as equal, a positive integer if the first is greater, and a negative integer if the first is smaller (see Array.sort for a complete specification). For example, Pervasives.compare is a suitable comparison function. The resulting list is sorted in increasing order. List.sort is guaranteed to run in constant heap space (in addition to the size of the result list) and logarithmic stack space.
The current implementation uses Merge Sort. It runs in constant heap space and logarithmic stack space. */

let stableSort: ('a => 'a => int) => list 'a => list 'a;
/* Same as List.sort, but the sorting algorithm is guaranteed to be stable (i.e. elements that compare equal are kept in their original order) .
The current implementation uses Merge Sort. It runs in constant heap space and logarithmic stack space. */

let fastSort: ('a => 'a => int) => list 'a => list 'a;
/* Same as List.sort or List.stableSort, whichever is faster on typical input. */

let sortUniq: ('a => 'a => int) => list 'a => list 'a;
/* Same as List.sort, but also remove duplicates. */

let merge: ('a => 'a => int) => list 'a => list 'a => list 'a;
/* Merge two lists: Assuming that l1 and l2 are sorted according to the comparison function cmp, merge cmp l1 l2 will return a sorted list containting all the elements of l1 and l2. If several elements compare equal, the elements of l1 will be before the elements of l2. Not tail-recursive (sum of the lengths of the arguments). */