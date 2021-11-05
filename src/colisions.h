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
	if(
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