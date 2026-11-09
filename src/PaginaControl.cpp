// Página web del control (HTML + CSS + JavaScript).
// Es solo texto guardado en la memoria flash: no necesita ser una clase.
#include "PaginaControl.h"

const char PAGINA_CONTROL[] PROGMEM = R"HTML(<!DOCTYPE html>
<html lang="es"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1,user-scalable=no,viewport-fit=cover">
<meta name="theme-color" content="#0d1117">
<title>Brazo Robótico</title>
<style>
:root{--fondo:#1a1c2c;--fondo2:#20233a;--k:#000;--t:#52b9a5;--tl:#8fd3c5;--tm:#45999b;--td:#33666a;
  --txt:#f4f4f4;--sub:#8b93af;--ok:#5ad16a;--okd:#2f7a3a;--mal:#e05252;--mald:#8a2a2a;
  --u:min(18vh,78px);--p:4px}
*{box-sizing:border-box;margin:0;-webkit-user-select:none;user-select:none;-webkit-tap-highlight-color:transparent}
html,body{height:100%}
body{font-family:"Courier New",ui-monospace,monospace;font-weight:700;text-transform:uppercase;color:var(--txt);
  background:var(--fondo);
  background-image:linear-gradient(45deg,var(--fondo2) 25%,transparent 25%,transparent 75%,var(--fondo2) 75%),
                   linear-gradient(45deg,var(--fondo2) 25%,transparent 25%,transparent 75%,var(--fondo2) 75%);
  background-size:32px 32px;background-position:0 0,16px 16px;
  touch-action:none;overflow:hidden;display:flex;flex-direction:column;gap:6px;
  padding:max(8px,env(safe-area-inset-top)) max(16px,env(safe-area-inset-right)) max(8px,env(safe-area-inset-bottom)) max(16px,env(safe-area-inset-left))}

/* Caja pixel: borde negro, esquinas recortadas, brillo arriba-izquierda y sombra abajo-derecha */
.px{--c:#2b2f4a;--cl:#3d4266;--cd:#1c1f33;background:var(--c);border:var(--p) solid var(--k);
  box-shadow:inset var(--p) var(--p) 0 var(--cl),inset calc(var(--p)*-1) calc(var(--p)*-1) 0 var(--cd);
  clip-path:polygon(0 var(--p),var(--p) var(--p),var(--p) 0,calc(100% - var(--p)) 0,calc(100% - var(--p)) var(--p),100% var(--p),
    100% calc(100% - var(--p)),calc(100% - var(--p)) calc(100% - var(--p)),calc(100% - var(--p)) 100%,var(--p) 100%,
    var(--p) calc(100% - var(--p)),0 calc(100% - var(--p)))}

/* Barra superior */
.top{display:flex;align-items:center;gap:10px}
.marca{display:flex;align-items:center;gap:8px;font-size:.9rem;letter-spacing:.1em;white-space:nowrap;padding:6px 10px;text-shadow:2px 2px 0 #000}
.led{width:10px;height:10px;background:var(--mal);box-shadow:0 0 0 2px #000}
.led.ok{background:var(--ok)}
.hud{flex:1;display:grid;grid-template-columns:repeat(4,1fr);gap:6px}
.g{padding:4px 8px}
.g .f{display:flex;justify-content:space-between;align-items:baseline;font-size:.6rem;color:var(--sub);letter-spacing:.06em}
.g b{font-size:1rem;color:var(--txt);text-shadow:2px 2px 0 #000}
.barra{height:6px;background:#000;margin-top:3px;padding:1px}
.barra i{display:block;height:100%;background:var(--t);box-shadow:inset 0 -2px 0 var(--td)}
.ico{width:38px;height:38px;color:var(--txt);font-size:1rem;font-family:inherit}

/* Mando */
.mando{flex:1;display:grid;grid-template-columns:1fr auto 1fr;align-items:center;justify-items:center;gap:10px}
.grupo{display:flex;flex-direction:column;align-items:center;gap:6px}
.etq{font-size:.7rem;color:var(--txt);letter-spacing:.12em;padding:3px 10px;text-shadow:2px 2px 0 #000}
.cruz{display:grid;grid-template-columns:repeat(3,var(--u));grid-template-rows:repeat(3,var(--u));gap:2px}
.col{display:grid;grid-template-rows:var(--u) var(--u);gap:6px;width:var(--u)}
.flecha{border:0;background:none;padding:0;touch-action:none;filter:drop-shadow(4px 4px 0 #0008);transition:transform .05s}
.flecha svg{width:100%;height:100%;display:block;shape-rendering:crispEdges}
.flecha.on{transform:translate(3px,3px);filter:drop-shadow(1px 1px 0 #0008) brightness(1.25)}
.centro{display:flex;flex-direction:column;align-items:center;gap:12px}

.btn{font-family:inherit;font-weight:700;color:var(--txt);text-shadow:2px 2px 0 #000;letter-spacing:.1em;touch-action:none;
  display:flex;align-items:center;justify-content:center;gap:8px;transition:transform .05s}
.btn.on{transform:translate(2px,3px);filter:brightness(1.25)}
.home{padding:8px 14px;font-size:.75rem}
.pinza{display:flex;flex-direction:column;gap:10px}
.pz{width:calc(var(--u)*2);height:calc(var(--u)*1.05);font-size:.95rem}
.pz.ab{--c:var(--ok);--cl:#9be8a3;--cd:var(--okd)}
.pz.ce{--c:var(--mal);--cl:#f29a9a;--cd:var(--mald)}

/* Aviso en vertical */
.girar{display:none;position:fixed;inset:0;background:var(--fondo);z-index:9;flex-direction:column;align-items:center;justify-content:center;gap:18px;text-align:center;padding:24px}
.girar .tel{width:48px;height:80px;--c:var(--t);--cl:var(--tl);--cd:var(--td);animation:rot 2s steps(4) infinite}
.girar p{color:var(--sub);font-size:.85rem}
@keyframes rot{0%,30%{transform:rotate(0)}60%,100%{transform:rotate(-90deg)}}
@media (orientation:portrait){.girar{display:flex}}
</style></head><body>

<div class="girar"><div class="tel px"></div><b>Gira el celular</b><p>Este control se usa en horizontal</p></div>

<header class="top">
  <div class="marca px"><span class="led" id="led"></span>BRAZO ROBÓTICO</div>
  <div class="hud" id="hud"></div>
  <button class="ico px btn" id="full" title="Pantalla completa">⛶</button>
</header>

<main class="mando">
  <section class="grupo">
    <div class="cruz">
      <span></span><button class="flecha" data-r="0" data-s="1" data-d="1"></button><span></span>
      <button class="flecha" data-r="270" data-s="0" data-d="1"></button><span></span><button class="flecha" data-r="90" data-s="0" data-d="-1"></button>
      <span></span><button class="flecha" data-r="180" data-s="1" data-d="-1"></button><span></span>
    </div>
    <span class="etq px">◀▶ Base · ▲▼ Hombro</span>
  </section>

  <section class="centro">
    <div class="grupo">
      <span class="etq px">Codo</span>
      <div class="col">
        <button class="flecha" data-r="0" data-s="2" data-d="1"></button>
        <button class="flecha" data-r="180" data-s="2" data-d="-1"></button>
      </div>
    </div>
    <button class="btn px home" id="ini">⟲ Inicio</button>
  </section>

  <section class="grupo">
    <span class="etq px">Pinza</span>
    <div class="pinza">
      <button class="btn px pz ab" data-s="3" data-d="-1">⟨ ⟩ Abrir</button>
      <button class="btn px pz ce" data-s="3" data-d="1">⟩ ⟨ Cerrar</button>
    </div>
  </section>
</main>

<script>
// Flecha pixel art dibujada en una cuadrícula de 14x15 (apunta hacia arriba; se rota con data-r)
// K=negro  T=verde agua  L=brillo  M=medio  D=sombra
const MAPA=[
"......KK......",
".....KMTK.....",
"....KMTTTK....",
"...KMTTTTTK...",
"..KMTTTTTTTK..",
".KMTTTTTTTTTK.",
"KLLLTTTTTTLLLK",
"KDDDKTTTTKDDDK",
"KKKKKMTTTKKKKK",
"....KMTTTK....",
"....KMTTTK....",
"....KMTTTK....",
"....KLLLLK....",
"....KDDDDK....",
"....KKKKKK...."];
const COL={K:'#000',T:'#52b9a5',L:'#8fd3c5',M:'#45999b',D:'#33666a'};
function flechaSVG(rot){
  let r='';
  MAPA.forEach((fila,y)=>[...fila].forEach((c,x)=>{if(COL[c])r+=`<rect x="${x}" y="${y}" width="1.02" height="1.02" fill="${COL[c]}"/>`;}));
  return `<svg viewBox="-0.5 0 15 15"><g transform="rotate(${rot} 7 7.5)">${r}</g></svg>`;
}
document.querySelectorAll('.flecha').forEach(b=>b.innerHTML=flechaSVG(+b.dataset.r));

const TICK=40;   // ms entre pasos
const PASO=1;    // grados por paso mientras se mantiene presionado (25°/s)
const PINZA=3;   // índice de la pinza
const AFLOJE=4;  // grados que la pinza afloja al soltar "Cerrar"
let S=[], A=[], vel=[0,0,0,0], ocupado=false, pendiente=false;
const $=id=>document.getElementById(id);

function conexion(ok){$('led').classList.toggle('ok',ok);}
function hud(){
  $('hud').innerHTML=S.map((s,i)=>{
    const p=(A[i]-s.min)/(s.max-s.min)*100;
    return `<div class="g px"><div class="f">${s.nombre}<b>${Math.round(A[i])}°</b></div><div class="barra"><i style="width:${p}%"></i></div></div>`;
  }).join('');
}
// Envía los 4 ángulos juntos; si hay una petición en curso deja una pendiente
function enviar(){
  if(!S.length) return;
  if(ocupado){pendiente=true;return;}
  ocupado=true;
  fetch('/todos?a='+A.map(Math.round).join(','))
    .then(r=>conexion(r.ok)).catch(()=>conexion(false))
    .finally(()=>{ocupado=false;if(pendiente){pendiente=false;enviar();}});
}
function mover(i,d){
  const s=S[i]; if(!s) return false;
  const n=Math.max(s.min,Math.min(s.max,A[i]+d));
  if(n===A[i]) return false;
  A[i]=n; return true;
}
// Bucle: mientras haya un botón presionado, avanza
setInterval(()=>{
  let c=false; vel.forEach((v,i)=>{if(v&&mover(i,v))c=true;});
  if(c){hud();enviar();}
},TICK);

document.querySelectorAll('[data-s]').forEach(b=>{
  const i=+b.dataset.s, d=+b.dataset.d;
  const soltar=()=>{
    if(!b.classList.contains('on'))return;
    b.classList.remove('on');vel[i]=0;
    // Al soltar "Cerrar" la pinza afloja un poco: sigue sujetando sin forzar el servo
    if(i===PINZA&&d>0){mover(i,-AFLOJE);hud();}
    enviar();
  };
  b.addEventListener('pointerdown',e=>{
    e.preventDefault(); b.setPointerCapture(e.pointerId); b.classList.add('on');
    try{navigator.vibrate&&navigator.vibrate(8);}catch(_){}
    if(mover(i,d*PASO)){hud();enviar();}
    vel[i]=d*PASO;
  });
  b.addEventListener('pointerup',soltar); b.addEventListener('pointercancel',soltar);
  b.addEventListener('contextmenu',e=>e.preventDefault());
});

function cargar(){
  fetch('/estado').then(r=>r.json()).then(d=>{S=d;A=d.map(s=>s.angulo);hud();conexion(true);}).catch(()=>conexion(false));
}
$('ini').addEventListener('click',()=>{vel=[0,0,0,0];fetch('/inicio').then(()=>setTimeout(cargar,100)).catch(()=>conexion(false));});
$('full').addEventListener('click',async()=>{
  try{
    if(document.fullscreenElement){await document.exitFullscreen();return;}
    await document.documentElement.requestFullscreen();
    await screen.orientation.lock('landscape');
  }catch(_){}
});
cargar();
setInterval(()=>{if(!ocupado)fetch('/estado').then(r=>conexion(r.ok)).catch(()=>conexion(false));},3000);
</script></body></html>)HTML";
