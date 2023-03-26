open System
// row and column constants
let ROWS= 3
let COLS = 3
// random # generator
let rnd = System.Random()

let generateMatrix() =
  let matrix = Array2D.init ROWS COLS (fun _ _ ->   rnd.Next(100))
  matrix

let multiplyMatrix() (m1 : int[,]) (m2 : int[,]) =
  let rec multAndSum () lis1 lis2 sum = 
    match lis1, lis2 with
     | [], [] -> sum //base case : if lis1 and lis2 are empty return sum
     | _ -> multAndSum() (lis1.Tail) (lis2.Tail) (sum + ((lis1.Head) * (lis2.Head))) 
  let result = Array2D.init ROWS COLS (fun r c -> multAndSum() ((m1.[r,*])|>Array.toList) ((m2.[*,c])|>Array.toList) 0  )
  result // return result

// generate two matricies
let m1 = generateMatrix()
let m2 = generateMatrix()
printfn "Matrix 1 :\n%A" m1
printfn "Matrix 2 : \n%A" m2

// multiply them together and print result
printfn "%A" (multiplyMatrix() m1 m2)

0 // return an integer exit code

