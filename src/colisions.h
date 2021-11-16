// colisão com mapa
bool check_if_inside_map(int x, int y, int px, int py, bool *value)
{
	if ((x >= px) && (x <= px+tileSiz) && (y >= py) && (y <= py+tileSiz))
		*value = false;

	if ((x >= px+1) && (x <= px+tileSiz-1) && (y >= py+1) && (y <= py+tileSiz-1))
		return true;
	
	return false;
}

void check_map_collision(int id, bool *direita, bool *esquerda, bool *baixo, bool *cima)
{
	if (mapa.map[id] == 0)
	{
		// ponto (x,y) do mapa
		int px = tileSiz * ( id % mapa.col );
		int py = tileSiz * ( id / mapa.col );
		
		int difx = px - player.posx;
		int dify = py - player.posy;
		if
		(
			((difx <= tileSiz) || (difx >= -tileSiz)) &&
			((dify <= tileSiz) || (dify >= -tileSiz))
		)
		{
			/* colisão por intervalo
				// pensando.
				*/
			// colisão por coordenada (ineficiente)
			int x, y;
			y = player.posy-1; // checa em cima
			for (x = player.posx+6; x <= (player.posx + ply_x-6); x++)
			{
				if (check_if_inside_map(x, y, px, py, cima))
					player.posy += 3;
				if (!(*cima))
				{
					break;
				}
			}

			y = player.posy + ply_y+1; // checa em baixo
			for (x = player.posx+6; x <= (player.posx + ply_x-6); x++)
			{
				if (check_if_inside_map(x, y, px, py, baixo))
					player.posy -= 3;
				if (!(*baixo))
					break;
			}

			x = player.posx-1; // checa a esquerda
			for (y = player.posy+1; y <= player.posy + ply_y-1; y++)
			{

				if (check_if_inside_map(x, y, px, py,esquerda))
					player.posx += 3;
				if (!(*esquerda))
					break;
			}

			x = player.posx + ply_x+1; // checa a direita
			for (y = player.posy+1; y <= player.posy + ply_y-1; y++)
			{

				if(check_if_inside_map(x, y, px, py, direita))
					player.posx -= 3;
				if (!(*direita))
					break;
			}
		}
	}
}

// colisão com caixas
void collide_with_box(int id)
{
	// analisa colis�es
	if (box[id].type == 0) // peça
	{
		box[id].existe = false;
		player.estado += 1;	
		return ;
	}
	else if (box[id].type == 1) // cilindro
	{
		player.oxygen += 400;
		box[id].existe = false;
		return ;
	}
	else if (box[id].type == 2) // meio cilindro
	{
		player.oxygen += 200;
		box[id].existe = false;
		return ;
	}
	else if (box[id].type == 3) // obstáculo
	{
		player.posx = mapa.inix;
		player.posy = mapa.iniy;
		player.oxygen -= 400;
		return ;
	}
	else if (box[id].type == 4) // gás
	{
		player.oxygen -= 5;
		return ;
	}
	else if (box[id].type == 9) //nave
	{
		if(player.estado == 2)
			player.estado +=1;
	}
	else if (box[id].type >= 10)
	{
		chat_stream(0, box[id].type - 10);
		box[id].existe = false;
	}
	else 
	{
		printf("Tipo de caixa errado");
		box[id].existe = false;
		return ;
	}
}
/*
bool check_if_inside_box(int x, int y, int id, int tamx, int tamy)
{
	if
	(
		(x >= box[id].posx) &&
		(x <= box[id].posx + tamx) &&
		(y >= box[id].posy) &&
		(y <= box[id].posy + tamy)
		)
	{
		return collide_with_box(id);
	}

	return false;
} */

void check_box_collision(int id, int tamx, int tamy)
{
	int difx = player.posx - box[id].posx;
	int dify = player.posy - box[id].posy;

	// checa se a caixa está encostada
	// precisão por interval (eficiente)
	if(
		(difx >=-ply_x)&&
		(difx <= tamx) &&
		(dify >=-ply_y)&&
		(dify <= tamy)
		)
	{
		collide_with_box(id);
		/* colisão por coordenada (ineficiente) 
		bool colidiu = false;
		int x, y;

		y = player.posy; // checa em cima
		for (x = player.posx; x < player.posx + ply_x; x++)
		{
			colidiu = check_if_inside_box(x, y, id, tamx, tamy);
			if (colidiu)
				break;
		}

		y = player.posy + ply_y; // checa em baixo
		for (x = player.posx; x < player.posx + ply_x; x++)
		{

			colidiu = check_if_inside_box(x, y, id, tamx, tamy);
			if (colidiu)
				break;
		}

		x = player.posx; // checa a esquerda
		for (y = player.posy; y < player.posy + ply_y; y++)
		{

			colidiu = check_if_inside_box(x, y, id, tamx, tamy);
			if (colidiu)
				break;
		}

		x = player.posx + ply_x; // checa a direita
		for (y = player.posy; y < player.posy + ply_y; y++)
		{

			colidiu = check_if_inside_box(x, y, id, tamx, tamy);
			if (colidiu)
				break;
		}
		*/
	}
}