import { useState, useEffect } from 'react'
import axios from "axios"
import Stack from '@mui/material/Stack';


export default function Ccr() {
  const [ccrs, setCcrs] = useState([]);
  const [novoCcrEmenta, setNovoCcrEmenta] = useState("");
  const [novoCcrDescricao, setNovoCcrDescricao] = useState("");
  const [novoCcrIdCurso, setNovoCcrIdCurso] = useState("");


  const buscaCcrs = async () => {
    try {
      const response = await axios.get("http://localhost:3002/ccr/todos");
      console.log(response.data);
      setCcrs(response.data.ccr);
    }
    catch (error) {
      console.log(error);
    }
  }

  useEffect(
    () => {
      buscaCcrs();
    },
    []
  )

  const cadastrarCcr = async () => {
    const response = await axios.post("http://localhost:3002/ccr", {
      descricao: novoCcrDescricao,
      ementa: novoCcrEmenta,
      id_curso: novoCcrIdCurso
    });
    console.log(response.data)
  }


  return (<>
    <ul>
      {ccrs.map((ccr) => {
        return <li key={ccr.id}>{ccr.descricao}</li>;
      })}
    </ul>
    <Stack spacing={1}>
      <Stack spacing={1} direction="row">
        <label>Descrição do ccr: </label>
        <input type="text" value={novoCcrDescricao} onChange={(event) => setNovoCcrDescricao(event.target.value)} />
      </Stack>
      <Stack spacing={1} direction="row">
        <label>Ementa do ccr: </label>
        <input type="text" value={novoCcrEmenta} onChange={(event) => setNovoCcrEmenta(event.target.value)} />
      </Stack>
      <Stack spacing={1} direction="row">
        <label>Id do Curso do ccr: </label>
        <input type="text" value={novoCcrIdCurso} onChange={(event) => setNovoCcrIdCurso(event.target.value)} />
      </Stack>
      <button onClick={cadastrarCcr} type="submit">Cadastrar Ccr</button>
    </Stack>
  </>)

}
