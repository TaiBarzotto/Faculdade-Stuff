import { useState, useEffect } from 'react'
import './App.css'
import Titulo from './Titulo'
import axios from "axios"

export default function App() {
  const [entrada, setEntrada] = useState("");
  const [cursos, setCursos] = useState([])
  
  const [count, setCount] = useState(0)
  const [exibirTitulo, setExibirTitulo] = useState(true)

  const incrementa = () => setCount(count+1)
  const controlaTitulo = () => setExibirTitulo(!exibirTitulo)

  const buscaCursos = async()=>{
    try{
      const response = await axios.get("http://localhost:3002/curso/todos");
      console.log(response.data);
      setCursos(response.data.curso);
    }
    catch{
      console.log(error);
    }
  }

  useEffect(
    ()=>{
      buscaCursos();
    },
    [count]
  );
  return (
    <>
      {exibirTitulo && <Titulo/>}
      <input type="text" value={entrada} onChange={(event)=> setEntrada (event.target.value)} />
      <p>{entrada}</p>
      <button onClick={controlaTitulo} type="submit">
          Exibir Titulo
      </button>
      <p>React</p>
      {cursos.length > 0 && <ul>
        {cursos.map((curso) => {
        return <li key={curso.id}>{curso.descricao}</li>;
          })}
      </ul>}
      <p>Valor do count: {count}</p>
      <button onClick={incrementa} type="submit">
      Incrementa
      </button>
    </>
    )
}

