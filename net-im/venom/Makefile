PORTNAME=	venom
PORTVERSION=	20140223
CATEGORIES=	net-im
MASTER_SITES=	GH

MAINTAINER=	derek@disflux.com
COMMENT=	A graphical client for the Tox core written in Vala/GTK. 

LICENSE=	GPLv3

USE_GITHUB=	yes
GH_ACCOUNT=	naxuroqa
GH_PROJECT=	Venom
GH_COMMIT=	ea6006e
GH_TAGNAME=	${GH_COMMIT}

DIST_SUBDIR=	${PORTNAME}

LIB_DEPENDS=	libgee.so:${PORTSDIR}devel/libgee \
    		libtoxcore.so:${PORTSDIR}net-im/tox-core
    		
BUILD_DEPENDS=	${LOCALBASE}/bin/valac:${PORTSDIR}/lang/vala

USES=		cmake
USE_GNOME=	gtk30

CMAKE_ENV=	PKG_CONFIG_PATH=/usr/local/lib/pkgconfig


.include <bsd.port.mk>
