// colisão com mapa
void check_if_inside_map(int x, int y, int px, int py, bool *value)
{
	if ((x >= px) && (x <= px+tileSiz) && (y >= py) && (y <= py+tileSiz))
		*value = false;
}

void check_map_collision(int id, bool *direita, bool *esquerda, bool *baixo, bool *cima)
{
	if (mapa.map[id] == 0)
	{
		// ponto (x,y) do mapa
		int px = tileSiz * ( id % mapa.col );
		int py = tileSiz * ( id / mapa.col );
		
		if
		(
			(difference_module(px, player.posx) <= tileSiz) &&
			(difference_module(py, player.posy) <= tileSiz)
		)
		{
			int x, y;
			y = player.posy-1; // checa em cima
			for (x = player.posx+1; x <= (player.posx + ply_x-1); x++)
			{
				check_if_inside_map(x, y, px, py, cima);
				if (!(*cima))
				{
					break;
				}
			}

			y = player.posy + ply_y+1; // checa em baixo
			for (x = player.posx+1; x <= (player.posx + ply_x-1); x++)
			{
				check_if_inside_map(x, y, px, py, baixo);
				if (!(*baixo))
					break;
			}

			x = player.posx-1; // checa a esquerda
			for (y = player.posy+1; y <= player.posy + ply_y-1; y++)
			{

				check_if_inside_map(x, y, px, py,esquerda);
				if (!(*esquerda))
					break;
			}

			x = player.posx + ply_x+1; // checa a direita
			for (y = player.posy+1; y <= player.posy + ply_y-1; y++)
			{

				check_if_inside_map(x, y, px, py, direita);
				if (!(*direita))
					break;
			}
		}
	}
}

// colisão com caixas
bool collide_with_box(int id)
{
	// analisa colis�es
	if (box[id].type == 2) // obst�culo
	{
		player.posx = mapa.inix;
		player.posy = mapa.iniy;
		player.oxygen -= 40;
		return true;
	}
	else if (box[id].type == 1) // cilindro
	{
		player.oxygen += 40;
		box[id].existe = false;
		return true;
	}
	else 
	{
		printf("Tipo de caixa errado");
		box[id].existe = false;
		return true;
	}
}

bool check_if_inside_box(int x, int y, int id, int tamx, int tamy)
{
	if
	(
		(x >= box[id].posx) &&
		(x <= box[id].posx + tamx) &&
		(y >= box[id].posy) &&
		(x <= box[id].posy + tamy)
		)
	{
		return collide_with_box(id);
	}

	return false;
}

void check_box_collision(int id, int tamx, int tamy)
{
	//checa se a caixa está perto
	// retira o módulo da distância
	// se está dentro dá área (NÃO CIRCULAR!) de 150 pixels
	if(
		(difference_module(box[id].posx, player.posx) < 150) &&
		(difference_module(box[id].posy, player.posy) < 150)
		)
	{
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
	}
}