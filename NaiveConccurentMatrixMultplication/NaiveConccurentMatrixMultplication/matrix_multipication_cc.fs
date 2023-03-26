
open System

// row and column constants
let ROWS= 3
let COLS = ROWS
// random # generator
let rnd = System.Random()

let generateMatrix() =
  let matrix = Array2D.init ROWS COLS (fun _ _ ->   rnd.Next(5,20))
  matrix

// recursive function that accepts two lists, multiplies their elements together and then 
// returns their dot product (the sum of the two lists products) 
let rec multAndSum() row col sum = 
   match row, col with
     | [], [] -> sum //base case : if row and col are empty return sum
     | _ -> multAndSum() (row.Tail) (col.Tail) (sum + ((row.Head) * (col.Head))) 
  
// this function uses the Array2D.init function. We will be removing this to implement concurrency.
// type specifiers are so that the compiler does not get upset when we use functions specific to 2D Arrays
let multiplyMatrix() (m1 : int[,]) (m2 : int[,]) =
  let result = Array2D.init ROWS COLS (fun r c -> multAndSum() ((m1.[r,*])|>Array.toList) ((m2.[*,c])|>Array.toList) 0  )
  result // return result

// outref<'T> is fsharp syntax for pass-by-reference for writing to a pointer 
let writeToMatrix (inputMatrix : outref<int[,]>) (x : int) (y : int) (data : int) =
  inputMatrix.[x, y] <- data  // write data to matrix at  given location
  inputMatrix                // return modifed matrix

//generate two matricies
let mutable m1 = generateMatrix()
let mutable m2 = generateMatrix()
printfn "Matrix 1 :\n%A" m1
printfn "Matrix 2 : \n%A" m2

// multiply them together and print result
printfn "Multiplied Matrix (Sequential):\n%A" (multiplyMatrix() m1 m2)

// empty mutable array for writing to
let mutable m3 = Array2D.init ROWS COLS (fun _ _ -> 0)


let work x y = async {
    let res= multAndSum() (m1.[x,*] |> Array.toList) (m2.[*,y] |> Array.toList) 0 
    printf " %A " res
    writeToMatrix &m3 x y res |> ignore 
    printfn "%A \n" m3
    res |> ignore 
}

printfn "Calling async function using 'Async.Parallel'...."
seq{for i in 0 .. ROWS-1 do for j in 0 .. COLS-1 do yield work i j }
  |> Async.Parallel 
  |> Async.RunSynchronously |>ignore


// result
printfn "\nprinting result matrix....\n%A" m3
