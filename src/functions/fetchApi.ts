interface disc {
  fs: string;
  type: string;
  size: number;
  used: number;
  available: number;
  use: number;
  mount: string;
}

interface data{
  cpu: number;
  gpu: number;
  mem: number;
  disc: Array<disc>;
}

async function getData() {
  //return await fetch("http://127.0.0.1:3000/api");
  return fetch("http://127.0.0.1:3000/api").then(res => {return res.json()})
}

export { getData, data };